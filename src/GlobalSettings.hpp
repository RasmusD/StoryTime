// Include guard
#ifndef __GlobalSettings_H_INCLUDED__
#define __GlobalSettings_H_INCLUDED__

#include <filesystem>
#include <stdint.h>
#include <iostream>

#include <SFML/Graphics.hpp>

namespace StoryTime {

typedef struct _Markup
{
  /*
  A list of currently active markup and its previous value as a string
  */
  std::vector<std::tuple<std::string, std::string, std::string> > activeMarkup;

  // Current text colour
  sf::Color colour = sf::Color::White;

  // Current background colour
  // This is only relevant for text segments and will define the background colour while a segment is active
  sf::Color backgroundColour = sf::Color::Black;

  // Current text speed
  float speed = 0.01f;

  // Current display image
  // TMP - see TODO
  std::string displayImage = "";
} Markup;

class GlobalSettings
{
  public:
    // Set defaults
    static void initialise();
    // Width of the game window
    static size_t WINDOWWIDTH;
    // Height of the game window
    static size_t WINDOWHEIGHT;
    // Default settings
    static Markup currentSettings;
    // The default font
    static sf::Font DEFAULTFONT;
    // The ROOT directory convenience path
    static std::filesystem::path ROOTDIR;
    // The saved game default directory
    static std::filesystem::path SAVEDIR;
    // Change CHARSIZE
    static void setCharSize(size_t newSize);
    // Change LINESPACE
    static void setLineSpacing(size_t newSize);
    // Get CHARSIZE
    static size_t getCharSize();
    // Get LINESPACE
    static size_t getLineSpacing();
    // See if something is initialised
    static bool isInitialised();
    // Print out the current settings that can be easily printed (for debug)
    static void printSettings();
  private:
    static bool INITIALISED;
    // The character size relative to the game window
    static size_t CHARSIZE;
    // The line spacing relative to the charsize
    static size_t LINESPACE;

};

} // end namespace StoryTime

#endif // __GlobalSettings_H_INCLUDED__;