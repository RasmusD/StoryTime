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
    // The character size relative to the game window
    static unsigned int CHARSIZE;
    // The line spacing relative to the charsize
    static unsigned int LINESPACE;
    // Default settings
    static Markup currentSettings;
    // The default font
    static sf::Font DEFAULTFONT;
};

} // end namespace StoryTime

#endif // __GlobalSettings_H_INCLUDED__;