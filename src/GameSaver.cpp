#include "GameSaver.hpp"

namespace StoryTime {

const std::string GameSaver::_version = "StoryTime Save File v0.1";

bool GameSaver::saveGame(std::filesystem::path& savepath,
                        std::unordered_set<std::string>& choiceHistory,
                        std::unordered_map<std::string, std::string>& storyData,
                        bool overwrite)
{
  if (overwrite == false and std::filesystem::is_regular_file(savepath) == true)
  {
    // We still give the player the chance to overwrite even when overwrite is set
    // to true (overwrite set to true should just be used for autosaving)
    if (_confirmOverwrite() == false)
    {
      return false;
    }
  }

  std::ofstream out(savepath);

  // Save save information
  out << "! " << _version << std::endl;

  // Save choice history
  out << "!";
  for (auto& choice : choiceHistory)
  {
    out << " " << choice;
  }
  out << std::endl;

  // Save story data
  for (auto& storyPiece : storyData)
  {
    out << storyPiece.first << " " << storyPiece.second << std::endl;
  }

  out.close();

  return true;
}

bool GameSaver::loadGame(std::filesystem::path& filepath)
{
  if (std::filesystem::is_regular_file(filepath) == false)
  {
    std::cerr << "LoadGame: Cannot load " << filepath << " as file does not exist." << std::endl;
    return false;
  }

  std::ifstream in(filepath);
  std::string line;

  std::vector<std::string> storyLines;
  std::unordered_map<std::string, std::string> storyData;

  while (std::getline(in, line))
  {
    if (line[0] == '!')
    {
      std::cout << line << std::endl;
    } else {
      storyLines.push_back(line);
    }
  }

  in.close();

  return StoryVerifier::parseAndVerifyStory(storyLines, storyData, true, false);
}

bool GameSaver::_confirmOverwrite()
{
  // TODO: Not implemented yet
  return false;
}

} // End namespace StoryTime