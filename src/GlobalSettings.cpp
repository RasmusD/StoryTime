#include "GlobalSettings.hpp"

namespace StoryTime {

// Default font
sf::Font GlobalSettings::DEFAULTFONT = sf::Font();
// Default settings
Markup GlobalSettings::currentSettings = Markup();

// Set the game window size
unsigned int GlobalSettings::WINDOWWIDTH = 1600;
unsigned int GlobalSettings::WINDOWHEIGHT = 1200;
unsigned int GlobalSettings::CHARSIZE = 30;
// We start with 1.5*charsize
unsigned int GlobalSettings::LINESPACE = GlobalSettings::CHARSIZE * 2;

void GlobalSettings::setCharSize(unsigned int newSize)
{
  CHARSIZE = newSize;
  LINESPACE = newSize * 2;
}

void GlobalSettings::setLineSpacing(unsigned int newSize)
{
  CHARSIZE = newSize / 2;
  LINESPACE = newSize;
}

int GlobalSettings::getCharSize()
{
  return CHARSIZE;
}

int GlobalSettings::getLineSpacing()
{
  return LINESPACE;
}

} // end namespace StoryTime