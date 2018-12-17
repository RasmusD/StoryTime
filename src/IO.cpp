#include "IO.hpp"

namespace StoryTime {

// List the contents of the given directory
std::vector<std::filesystem::path> IO::ListDirectory(std::filesystem::path& dirPath)
{
  std::vector<std::filesystem::path> files;
  for (auto& file : std::filesystem::directory_iterator(dirPath))
  {
    files.push_back(file.path());
  }
  return files;
}

bool IO::Save(std::filesystem::path savePath,
              std::filesystem::path storyPath,
              std::string& curBranch,
              std::unordered_set<std::string>& choice_history)
{
  std::filesystem::path dir_path = savePath;
  dir_path.remove_filename();
  if (std::filesystem::is_directory(dir_path) == false)
  {
    std::cout << "IO::Save: Save file path is not valid!" << std::endl;
    return false;
  }

  if (std::filesystem::is_regular_file(storyPath) == false)
  {
    std::cout << "IO::Save: Cannot find story path!" << std::endl;
    return false;
  }

  std::ofstream of(savePath);

  // save the story played
  of << storyPath << std::endl;

  // save the current branch name
  of << curBranch << std::endl;

  // save the choices made
  for (auto& choice : choice_history)
  {
    of << choice << std::endl;
  }

  of.close();

  return true;
}

bool IO::Load(std::filesystem::path savePath,
              std::filesystem::path& storyPath,
              std::string& curBranch,
              std::unordered_set<std::string>& choice_history)
{
  if (std::filesystem::is_regular_file(savePath) == false)
  {
    std::cout << "IO::Load: Save path given does not exist!" << std::endl;
    return false;
  }

  std::ifstream save(savePath);
  std::string line;

  int count = 0;
  while (std::getline(save, line))
  {
    if (count == 0)
    {
      storyPath = std::filesystem::path(line);
      if (std::filesystem::is_regular_file(storyPath) == false)
      {
        std::cout << "IO::Load: Story path given does not exist! Please install to play this save..." << std::endl;
        return false;
      }
    } else if (count == 1)
    {
      curBranch = line;
    } else {
      choice_history.insert(line);
    }
    count++;
  }

  return true;
}

} // End namespace StoryTime