#include "OpeningScreen.hpp"

namespace StoryTime {

OpeningScreen::OpeningScreen() : GameSlice()
{
  if (!_titleFont.loadFromFile("../resources/fonts/rosegarden/Rosegarden.ttf"))
  {
    throw std::runtime_error("Cannot load Rosegarden font!");
  }

  _changeSlice = false;

  _titleText.setFont(_titleFont);
  _titleText.setString("StoryTime");
  _titleText.setCharacterSize(GlobalSettings::WINDOWHEIGHT / 10);
  _titleText.setFillColor(sf::Color::White);
  _titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
  _titleTextRect = _titleText.getLocalBounds();
  _titleText.setOrigin(_titleTextRect.left + _titleTextRect.width / 2.0f, _titleTextRect.top + _titleTextRect.height / 2.0f);
  _titleText.setPosition(sf::Vector2f(GlobalSettings::WINDOWWIDTH / 2.0f, GlobalSettings::WINDOWHEIGHT / 2.0f));
}

void OpeningScreen::takeInput(sf::Event& curEvent, sf::RenderWindow& renderWindow)
{
  switch (curEvent.type)
  {
    case sf::Event::MouseButtonReleased:
      _changeSlice = true;
      break;
    default:
      break;
  }
}

GameSlice* OpeningScreen::update(sf::Time& elapsedTime, sf::RenderWindow& renderWindow)
{
  if (_changeSlice == true)
  {
    return new MenuScreen();
  }
  
  return NULL;
}

void OpeningScreen::draw(sf::RenderWindow& renderWindow)
{
  renderWindow.draw(_titleText);
}

} // End namespace StoryTime