#include <fstream>

#include "StoryVerifier.hpp"

int usage()
{
  std::cerr << "Usage: verifyStory storyPath [strictVerification]" << std::endl;
  std::cerr << "storyPath               :     Path to story to verify." << std::endl;
  std::cerr << "strictVerification      :     Should some non-crucial elements like non-touched segments count as a fail? [optional, default=true]" << std::endl;
  return 1;
}

int main(int argc, char *argv[])
{
  if (argc < 2 or argc > 3)
  {
    return usage();
  }

  bool strictVerification = true;
  if (argc == 3)
  {
    if (std::string(argv[2]) == "false")
    {
      strictVerification = false;
    } else if (std::string(argv[2]) == "true")
    {
      strictVerification = true;
    } else
    {
      std::cerr << "strictVerification must be false or true." << std::endl;
      return usage();
    } 
  }

  std::unordered_map<std::string, std::string> story;
  // Verify the story
  if (StoryTime::StoryVerifier::loadAndVerifyStory(std::string(argv[1]), story, true, strictVerification) == false)
  {
    std::cout << "\nStory (" + std::string(argv[1]) + ") not valid!" << std::endl;
  } else {
    std::cout << "\nStory (" + std::string(argv[1]) + ") is valid!" << std::endl;
  }
  return 0;
}