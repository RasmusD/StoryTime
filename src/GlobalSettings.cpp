#include "GlobalSettings.hpp"

namespace StoryTime {

sf::Font GlobalSettings::DEFAULTFONT = sf::Font();
// Default settings
Markup GlobalSettings::currentSettings = Markup();

// Set the game window size
unsigned int GlobalSettings::WINDOWWIDTH = 1600;
unsigned int GlobalSettings::WINDOWHEIGHT = 1200;
unsigned int GlobalSettings::CHARSIZE = 30;
// We start with 1.5*charsize
unsigned int GlobalSettings::LINESPACE = GlobalSettings::CHARSIZE * 2;

} // end namespace StoryTime