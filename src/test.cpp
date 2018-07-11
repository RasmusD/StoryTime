#include <filesystem>

#include "IO.hpp"


int main(int argc, char **argv)
{
  std::filesystem::path path("stories");
  for (auto& f : StoryTime::IO::ListDirectory(path))
  {
    std::cout << f << std::endl;
  }

  return 0;
}