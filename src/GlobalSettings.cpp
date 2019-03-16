#include "GlobalSettings.hpp"

namespace StoryTime {

size_t GlobalSettings::WINDOWWIDTH = 10;
size_t GlobalSettings::WINDOWHEIGHT = 10;
Markup GlobalSettings::currentSettings = Markup();
sf::Font GlobalSettings::DEFAULTFONT = sf::Font();
std::filesystem::path GlobalSettings::ROOTDIR = "";
std::filesystem::path GlobalSettings::SAVEDIR = "";
bool GlobalSettings::INITIALISED = false;
size_t GlobalSettings::CHARSIZE = 10;
size_t GlobalSettings::LINESPACE = 10;

void GlobalSettings::initialise()
{
  ROOTDIR = std::filesystem::current_path();
  SAVEDIR = ROOTDIR;
  SAVEDIR /= "saves";
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
  WINDOWHEIGHT = 1000;
  CHARSIZE = 30;
  // We start with 1.5*charsize
  LINESPACE = CHARSIZE * 2;
  INITIALISED = true;
}

void GlobalSettings::setCharSize(size_t newSize)
{
  CHARSIZE = newSize;
  LINESPACE = newSize * 2;
}

void GlobalSettings::setLineSpacing(size_t newSize)
{
  CHARSIZE = newSize / 2;
  LINESPACE = newSize;
}

size_t GlobalSettings::getCharSize()
{
  return CHARSIZE;
}

size_t GlobalSettings::getLineSpacing()
{
  return LINESPACE;
}

bool GlobalSettings::isInitialised()
{
  return INITIALISED;
}

void GlobalSettings::printSettings()
{
  std::cout << "WindowWidth: " << WINDOWWIDTH << std::endl;
  std::cout << "WindowHeight: " << WINDOWHEIGHT<< std::endl;
  std::cout << "RootDir: " << ROOTDIR << std::endl;
  std::cout << "Initialised: " << INITIALISED << std::endl;
  std::cout << "CharSize: " << CHARSIZE << std::endl;
  std::cout << "LineSpace: " << LINESPACE << std::endl;
}

} // end namespace StoryTime

