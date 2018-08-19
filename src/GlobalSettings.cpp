#include "GlobalSettings.hpp"

namespace StoryTime {

unsigned int GlobalSettings::WINDOWWIDTH = 10;
unsigned int GlobalSettings::WINDOWHEIGHT = 10;
Markup GlobalSettings::currentSettings = Markup();
sf::Font GlobalSettings::DEFAULTFONT = sf::Font();
std::filesystem::path GlobalSettings::ROOTDIR = "";
bool GlobalSettings::INITIALISED = false;
unsigned int GlobalSettings::CHARSIZE = 10;
unsigned int GlobalSettings::LINESPACE = 10;

void GlobalSettings::initialise()
{
  ROOTDIR = std::filesystem::current_path();
  // Default font
  std::filesystem::path fontPath = ROOTDIR;
  fontPath /= std::filesystem::path("resources/fonts/rosegarden/Rosegarden.ttf");
  DEFAULTFONT = sf::Font();
  if (!DEFAULTFONT.loadFromFile(fontPath.string()))
  {
    throw std::runtime_error("Cannot load Rosegarden font!");
  }
  // Default settings
  currentSettings = Markup();

  // Set the game window size
  WINDOWWIDTH = 1600;
  WINDOWHEIGHT = 1200;
  CHARSIZE = 30;
  // We start with 1.5*charsize
  LINESPACE = GlobalSettings::CHARSIZE * 2;
  INITIALISED = true;
}

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

bool GlobalSettings::isInitialised()
{
  return INITIALISED;
}

} // end namespace StoryTime