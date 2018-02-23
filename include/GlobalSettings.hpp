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

  // Another test markup
  double test2 = 0.0;
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

    // The default text speed
    static float DEFAULTTEXTSPEED;
    // The default font
    static sf::Font DEFAULTFONT;
};

} // end namespace StoryTime

#endif // __GlobalSettings_H_INCLUDED__;