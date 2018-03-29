// A tool for verifying the correctness of a story

#include "StoryVerifier.hpp"

namespace StoryTime {

bool StoryVerifier::loadAndVerifyStory(std::string storyPath, std::unordered_map<std::string, std::string>& storyData, bool print)
{
  // Open story and find segments
  std::ifstream input(storyPath, std::ios::in);
  if (!input)
  {
    std::cerr << "StoryVerifier: File " + storyPath + " doesn't exist!" << std::endl;
    return false; 
  }

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
  for (auto& segment : storyData)
  {
    std::deque<Utils::SegChoice> segmentQueue;
    TextParser::parseText(segment.second, segmentQueue);
    // A bool to check if a branching choice has already been found in segment
    bool branchFound = false;
    // Find the branching choice of this segment
    for (auto& segChoice : segmentQueue)
    {
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
        }
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
  }

  // Verify that all paths eventually lead to [end]
  // This is a depth first search
  std::unordered_set<std::string> history = {};
  std::string beg = "[begin]";
  return verifyPaths(paths, beg, history, print);
}

bool StoryVerifier::verifyPaths(std::unordered_map<std::string, std::vector<std::string>>& paths,
                                std::string& startKey,
                                std::unordered_set<std::string> history,
                                bool print)
{
  history.insert(startKey);
  for (auto& pathEnds : paths[startKey])
  {
    if (pathEnds == "[end]")
    {
      continue;
    } else if (paths.count(pathEnds) == 0)
    {
      std::cerr << "StoryVerifier: Branch (" + pathEnds + ") not found!" << std::endl;
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
      } else if (verifyPaths(paths, pathEnds, history, print) == false)
      {
        return false;
      }
    }
  }
  // Woop!
  if (print)
  {
    std::cerr << "StoryVerifier: All branches from (" + startKey + ") reach [end]!" << std::endl;
  }
  return true;
}

} // End namespace StoryTime
