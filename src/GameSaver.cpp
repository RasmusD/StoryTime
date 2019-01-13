#include "GameSaver.hpp"

namespace StoryTime {

const std::string GameSaver::_version = "StoryTime Save File v0.1";

bool GameSaver::saveGame(std::filesystem::path& savepath, bool overwrite)
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

  out << "!" << _version << std::endl;

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

  while (std::getline(in, line))
  {
    std::cout << line;
  }

  in.close();

  return true;
}

bool GameSaver::_confirmOverwrite()
{
  // TODO: Not implemented yet
  return false;
}

} // End namespace StoryTime