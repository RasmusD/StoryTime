#include <fstream>

#include "StoryVerifier.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: verifyStory storyPath" << std::endl;
    return 1;
  }

  std::unordered_map<std::string, std::string> story;
  // Verify the story
  if (StoryTime::StoryVerifier::loadAndVerifyStory(std::string(argv[1]), story, true, true) == false)
  {
    std::cout << "\nStory (" + std::string(argv[1]) + ") not valid!" << std::endl;
  } else {
    std::cout << "\nStory (" + std::string(argv[1]) + ") is valid!" << std::endl;
  }
  return 0;
}