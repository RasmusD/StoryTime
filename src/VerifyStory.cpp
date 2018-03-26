#include <fstream>

#include "StoryVerifier.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: verifyStory storyPath" << std::endl;
    return 1;
  }
  std::ifstream input(argv[1], std::ios::in);
  if (!input)
  {
    std::cerr << "File " + std::string(argv[1]) + " doesn't exist!" << std::endl;
    return 1; 
  }

  std::unordered_map<std::string, std::string> story;
  std::pair<std::string, std::string> segment = {"" ,""};
  for(std::string line; getline(input, line); )
  {
    if (line.front() == '[')
    {
      // Split once on first whitespace
      if (segment.first != "")
      {
        story.insert(segment);
        segment = {"", ""};
      }
      size_t wPos = line.find_first_of(' ');
      segment.first = line.substr(0, wPos);
      segment.second = line.substr(wPos+1, std::string::npos);
    } else {
      segment.second += '\n' + line;
    }
  }

  // Add the last segment
  story.insert(segment);
  
  input.close();
  // Verify the story
  if (StoryTime::StoryVerifier::verifyStory(story) == false)
  {
    std::cout << "\nStory (" + std::string(argv[1]) + ") not valid!" << std::endl;
  } else {
    std::cout << "\nStory (" + std::string(argv[1]) + ") is valid!" << std::endl;
  }
  return 0;
}