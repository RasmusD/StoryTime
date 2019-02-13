#include "GameSaver.hpp"

namespace StoryTime {

const std::string GameSaver::_version = "StoryTime Save File v0.1";

bool GameSaver::saveGame(std::filesystem::path& savepath,
                        std::unordered_set<std::string>& choiceHistory,
                        std::unordered_map<std::string, std::string>& storyData,
                        std::string& currentSegment,
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
  out << "!!";
  for (auto& choice : choiceHistory)
  {
    out << " " << choice;
  }
  out << std::endl;

  // Save current segment id
  out << "!!! " << currentSegment << std::endl;

  // Save story data
  for (auto& storyPiece : storyData)
  {
    out << storyPiece.first << " " << storyPiece.second << std::endl;
  }

  out.close();

  return true;
}

bool GameSaver::loadGame(std::filesystem::path& filepath,
                          std::unordered_map<std::string, std::string>& storyData,
                          std::unordered_set<std::string>& choiceHistory,
                          std::string& startSegment)
{
  if (std::filesystem::is_regular_file(filepath) == false)
  {
    std::cerr << "LoadGame: Cannot load " << filepath << " as file does not exist." << std::endl;
    return false;
  }

  std::ifstream in(filepath);
  std::string line;

  std::vector<std::string> storyLines;

  while (std::getline(in, line))
  {
    if (line[0] == '!')
    {
      if (line[1] == '!')
      {
        if (line[2] == '!')
        {
          // Current segment
          startSegment = line.substr(4);
        } else {
          // Choice history
          Utils::splitStringToSet(line.substr(3), choiceHistory, " ");
        }
      } else {
        // Version information
        std::cout << line << std::endl;
      }
    } else {
      storyLines.push_back(line);
    }
  }

  in.close();

  return StoryVerifier::parseAndVerifyStory(storyLines, storyData, false, false);
}

bool GameSaver::_confirmOverwrite()
{
  // TODO: Not implemented yet
  return false;
}

} // End namespace StoryTime