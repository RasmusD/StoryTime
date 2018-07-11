// The main game

// Include guard
#ifndef __IO_H_INCLUDED__
#define __IO_H_INCLUDED__

#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

namespace StoryTime {

class IO
{
  public:
    // List the contents of the given directory
    static std::vector<std::string> ListDirectory(std::filesystem::path& dirPath);
};

} // End namespace StoryTime


#endif // __IO_H_INCLUDED__;