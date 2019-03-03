// A tool for verifying the correctness of a story

#include "StoryVerifier.hpp"

namespace StoryTime {

bool StoryVerifier::loadAndVerifyStory(const std::filesystem::path& storyPath,
                                      std::unordered_map<std::string, std::string>& storyData,
                                      const bool& print,
                                      const bool& strictVerification)
{
  // Open story and find segments
  if (!std::filesystem::is_regular_file(storyPath))
  {
    std::cerr << "StoryVerifier: File " + storyPath.string() + " doesn't exist!" << std::endl;
    return false; 
  }

  std::ifstream input(storyPath, std::ios::in);
  std::pair<std::string, std::string> storySegment = {"" ,""};
  for(std::string line; getline(input, line); )
  {
    if (line.front() == '[')
    {
      // Split once on first whitespace
      if (storySegment.first != "")
      {
        // Check this is not a duplicate branch name
        // If it already exists we have duplicate branch names
        if (storyData.count(storySegment.first) > 0)
        {
          std::cerr << "StoryVerifier: Duplicate branch name (" << storySegment.first << ")!" << std::endl;
          return false;
        }
        storyData.insert(storySegment);
        storySegment = {"", ""};
      }
      size_t wPos = line.find_first_of(' ');
      storySegment.first = line.substr(0, wPos);
      storySegment.second = line.substr(wPos+1, std::string::npos);
    } else {
      storySegment.second += '\n' + line;
    }
  }

  // Add the last segment
  storyData.insert(storySegment);
  
  input.close();

  return verifyStory(storyData, storyPath, print, strictVerification);
}

bool StoryVerifier::parseAndVerifyStory(std::vector<std::string>& storyLines,
                                      std::unordered_map<std::string, std::string>& storyData,
                                      const std::filesystem::path& storyPath,
                                      const bool& print,
                                      const bool& strictVerification)
{
  std::pair<std::string, std::string> storySegment = {"" ,""};
  for(auto& line : storyLines)
  {
    if (line.front() == '[')
    {
      // Split once on first whitespace
      if (storySegment.first != "")
      {
        // Check this is not a duplicate branch name
        // If it already exists we have duplicate branch names
        if (storyData.count(storySegment.first) > 0)
        {
          std::cerr << "StoryVerifier: Duplicate branch name (" << storySegment.first << ")!" << std::endl;
          return false;
        }
        storyData.insert(storySegment);
        storySegment = {"", ""};
      }
      size_t wPos = line.find_first_of(' ');
      storySegment.first = line.substr(0, wPos);
      storySegment.second = line.substr(wPos+1, std::string::npos);
    } else {
      storySegment.second += '\n' + line;
    }
  }

  // Add the last segment
  storyData.insert(storySegment);

  return verifyStory(storyData, storyPath, print, strictVerification);
}

bool StoryVerifier::verifyStory(std::unordered_map<std::string, std::string>& storyData,
                                  const std::filesystem::path& storyPath,
                                  const bool& print,
                                  const bool& strictVerification)
{
  // Check we have a start and end segment
  if (storyData.count("[begin]") == 0)
  {
    std::cerr << "StoryVerifier: No [begin] segment!" << std::endl;
    return false;
  }
  if (storyData.count("[end]") == 0)
  {
    std::cerr << "StoryVerifier: No [end] segment!" << std::endl;
    return false;
  }
  // Now make a set of paths and verify that they all lead to [end]
  std::unordered_map<std::string, std::vector<std::string> > paths;
  Markup defaultMarkup = Markup();
  // Set of used resources
  std::unordered_set<std::string> images;
  for (auto& segment : storyData)
  {
    std::deque<Utils::SegChoice> segmentQueue;
    TextParser::parseText(segment.second, segmentQueue, defaultMarkup);
    // A bool to check if a branching choice has already been found in segment
    bool branchFound = false;
    // Find the branching choice of this segment
    for (auto& segChoice : segmentQueue)
    {
      Markup segmentMarkup;
      if (segChoice.choice)
      {
        if (segChoice.choice->getChoiceType() == ChoiceType::BRANCH)
        {
          paths[segment.first] = {};
          paths[segment.first].reserve(segChoice.choice->getNumChoices());
          for (auto& choice : segChoice.choice->getChoices())
          {
            paths[segment.first].push_back(choice.id);
          }
          if (branchFound == false)
          {
            branchFound = true;
          } else {
            std::cerr << "StoryVerifier: Multiple branching choices in segment!" << std::endl;
            return false;
          }
          segmentMarkup = segChoice.choice->getSettings();
        }
      } else {
        segmentMarkup = segChoice.text->getSettings();
      }

      if (segmentMarkup.displayImage != "")
      {
        images.insert(segmentMarkup.displayImage);
      }
    }
  }

  if (print)
  {
    std::cout << "Path pairs:" << std::endl;
    for (auto& pathPair : paths)
    {
      std::cout << "Source: " << pathPair.first << " Ends: ";
      for (auto& end : pathPair.second)
      {
        std::cout << end << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl << "Used resources:" << std::endl;
    for (auto& image : images)
    {
      std::cout << image << std::endl;
    }
  }

  // Check all resources exist, this will be the case if we can create a resource object
  bool resourcesValid;
  try
  {
    StoryResources resources = StoryResources(storyPath, images);
    if (print)
    {
      std::cout << "Resources are valid!" << std::endl; 
    }
    resourcesValid = true;
  } catch (...)
  {
    if (print)
    {
      std::cout << "Resources are not valid!" << std::endl; 
    }
    resourcesValid = false;
  }

  // Verify that all paths eventually lead to [end]
  // This is a depth first search
  // The history of each path token
  // Passed as copy for each token to have individual history
  std::unordered_set<std::string> history = {};
  // A set of paths which have 
  std::unordered_set<std::string> pathsTouched = {"[begin]"};
  std::string beg = "[begin]";
  bool storyValid;
  if (strictVerification)
  {
    if (verifyPaths(paths, beg, history, pathsTouched, print))
    {
      // Check if all paths have been touched
      for (auto storyPair : storyData)
      {
        // We ignore settings
        if (storyPair.first != "[settings]")
        {
          if (pathsTouched.count(storyPair.first) == 0)
          {
            if (print)
            {
              std::cout << "StoryVerifier: " << storyPair.first << " is an unreachable segment!" << std::endl;
            }
            storyValid = false;
            break;
          }
        }
      }
      storyValid =  true;
    } else {
      storyValid = false;
    }
  } else {
    storyValid = verifyPaths(paths, beg, history, pathsTouched, print);
  }

  if (storyValid == true && resourcesValid)
  {
    return true;
  } else {
    return false;
  }
}

bool StoryVerifier::verifyPaths(std::unordered_map<std::string, std::vector<std::string>>& paths,
                                std::string& startKey,
                                std::unordered_set<std::string> history,
                                std::unordered_set<std::string>& pathsTouched,
                                const bool& print)
{
  history.insert(startKey);
  for (auto& pathEnds : paths[startKey])
  {
    pathsTouched.insert(pathEnds);
    if (pathEnds == "[end]")
    {
      continue;
    } else if (paths.count(pathEnds) == 0)
    {
      std::cout << "StoryVerifier: Branch (" + pathEnds + ") not found!" << std::endl;
      return false;
    } else
    {
      // To avoid infinite loops check that we've not already been here
      if (history.count(pathEnds) > 0)
      {
        if (print)
        {
          std::cout << "From (" + startKey + ") to (" + pathEnds + ") is a loop." << std::endl;
        }
      } else if (verifyPaths(paths, pathEnds, history, pathsTouched, print) == false)
      {
        return false;
      }
    }
  }
  // Woop!
  if (print)
  {
    std::cout << "StoryVerifier: All branches from (" + startKey + ") reach [end]!" << std::endl;
  }
  return true;
}

} // End namespace StoryTime
