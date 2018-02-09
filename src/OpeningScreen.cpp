#include "OpeningScreen.hpp"

namespace StoryTime {

OpeningScreen::OpeningScreen() : GameSlice()
{
  if (!_titleFont.loadFromFile("../resources/fonts/rosegarden/Rosegarden.ttf"))
  {
    std::cerr << "Cannot load Rosegarden font!" << std::endl;
    throw;
  }

  _titleText.setFont(_titleFont);
  _titleText.setString("StoryTime");
  _titleText.setCharacterSize(GlobalSettings::WINDOWHEIGHT / 10);
  _titleText.setFillColor(sf::Color::White);
  _titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
  _titleTextRect = _titleText.getLocalBounds();
  _titleText.setOrigin(_titleTextRect.left + _titleTextRect.width / 2.0f, _titleTextRect.top + _titleTextRect.height / 2.0f);
  _titleText.setPosition(sf::Vector2f(GlobalSettings::WINDOWWIDTH / 2.0f, GlobalSettings::WINDOWHEIGHT / 2.0f));
}

GameSlice* OpeningScreen::update(sf::Time& elapsedTime, sf::Event& curEvent, sf::Event& prevEvent, sf::RenderWindow& renderWindow)
{
  switch (curEvent.type)
  {
    case sf::Event::MouseButtonReleased:
      if (prevEvent.type == sf::Event::MouseButtonPressed)
      {
        return new MenuScreen();
      }
      break;
    default:
      break;
  }
  
  return NULL;
}

void OpeningScreen::draw(sf::RenderWindow& renderWindow)
{
  renderWindow.draw(_titleText);
}

} // End namespace StoryTime