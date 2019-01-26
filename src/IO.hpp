// The main game

// Include guard
#ifndef __IO_H_INCLUDED__
#define __IO_H_INCLUDED__

#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <unordered_set>

namespace StoryTime {

class IO
{
  public:
    // List the contents of the given directory
    static std::vector<std::filesystem::path> ListDirectory(std::filesystem::path& dirPath);

    // Create a save file for a story
    static bool Save(std::filesystem::path filePath,
                    std::filesystem::path storyPath,
                    std::string& curBranch,
                    std::unordered_set<std::string>& choice_history);

    static bool Load(std::filesystem::path savePath,
                    std::filesystem::path& storyPath,
                    std::string& curBranch,
                    std::unordered_set<std::string>& choice_history);
};

} // End namespace StoryTime


#endif // __IO_H_INCLUDED__;