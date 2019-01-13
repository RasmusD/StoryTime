#include <filesystem>

#include "GameSaver.hpp"


int main(int argc, char **argv)
{
  std::filesystem::path saveFile = std::filesystem::current_path();
  saveFile /= "testSave.save";
  StoryTime::GameSaver::saveGame(saveFile, true);

  StoryTime::GameSaver::loadGame(saveFile);

  return 0;
}