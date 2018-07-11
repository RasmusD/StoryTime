#include "IO.hpp"

namespace StoryTime {

// List the contents of the given directory
std::vector<std::string> IO::ListDirectory(std::filesystem::path& dirPath)
{
  std::vector<std::string> files;
  for (auto& file : std::filesystem::directory_iterator(dirPath))
  {
    files.push_back(file.path());
  }
  return files;
}

} // End namespace StoryTime