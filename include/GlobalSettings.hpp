// Include guard
#ifndef __GlobalSettings_H_INCLUDED__
#define __GlobalSettings_H_INCLUDED__

#include <stdint.h>
#include <iostream>

#include <SFML/Graphics.hpp>

namespace StoryTime {

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