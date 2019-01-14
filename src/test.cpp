#include <filesystem>
#include <unordered_set>
#include <unordered_map>

#include "StoryVerifier.hpp"
#include "GameSaver.hpp"

int main(int argc, char **argv)
{
  std::filesystem::path saveFile = std::filesystem::current_path();
  saveFile /= "testSave.save";
  std::unordered_set<std::string> choices;
  choices.insert("Test");
  choices.insert("Test2");
  choices.insert("Test3");
  std::unordered_map<std::string, std::string> storyData;
  StoryTime::StoryVerifier::loadAndVerifyStory("/home/rasmus/GitRepos/StoryTime/stories/test.story", storyData, false, false);
  StoryTime::GameSaver::saveGame(saveFile, choices, storyData, true);

  StoryTime::GameSaver::loadGame(saveFile);

  return 0;
}