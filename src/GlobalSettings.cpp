#include "GlobalSettings.hpp"

namespace StoryTime {

sf::Font GlobalSettings::DEFAULTFONT = sf::Font();
// Default text speed
// Lower is faster
float GlobalSettings::DEFAULTTEXTSPEED = 0.01;

// Set the game window size
unsigned int GlobalSettings::WINDOWWIDTH = 1600;
unsigned int GlobalSettings::WINDOWHEIGHT = 1200;
unsigned int GlobalSettings::CHARSIZE = 30;
// We start with 1.5*charsize
unsigned int GlobalSettings::LINESPACE = GlobalSettings::CHARSIZE * 2;

} // end namespace StoryTime