// Include guard
#ifndef __GlobalSettings_H_INCLUDED__
#define __GlobalSettings_H_INCLUDED__

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
  float speed = 0.01;
} Markup;

class GlobalSettings
{
  public:
    // Width of the game window
    static unsigned int WINDOWWIDTH;
    // Height of the game window
    static unsigned int WINDOWHEIGHT;
    // Default settings
    static Markup currentSettings;
    // The default font
    static sf::Font DEFAULTFONT;
    // Change CHARSIZE
    static void setCharSize(unsigned int newSize);
    // Change LINESPACE
    static void setLineSpacing(unsigned int newSize);
    // Get CHARSIZE
    static int getCharSize();
    // Get LINESPACE
    static int getLineSpacing();
  private:
    // The character size relative to the game window
    static unsigned int CHARSIZE;
    // The line spacing relative to the charsize
    static unsigned int LINESPACE;

};

} // end namespace StoryTime

#endif // __GlobalSettings_H_INCLUDED__;