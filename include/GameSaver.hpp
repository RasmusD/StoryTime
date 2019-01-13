// Static class for saving the state of a game to be loaded later and for loading a save file

// Include guard
#ifndef __MainGame_H_INCLUDED__
#define __MainGame_H_INCLUDED__

#include <filesystem>
#include <iostream>
#include <fstream>

namespace StoryTime {

class GameSaver
{
  public:
    // Save a game to load later
    static bool saveGame(std::filesystem::path& savepath, bool overwrite);
    // Load a game saved to load later
    static bool loadGame(std::filesystem::path& filepath);
  private:
    // Ask the user if file should be overwritten
    static bool _confirmOverwrite();
    // The version string for save files
    static const std::string _version;
};


} // End namespace StoryTime


#endif // __GameSaver_H_INCLUDED__;