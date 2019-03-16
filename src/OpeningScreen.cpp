#include "OpeningScreen.hpp"

namespace StoryTime {

OpeningScreen::OpeningScreen() : GameSlice()
{
  _titleFont = GlobalSettings::DEFAULTFONT;

  _changeSlice = false;

  _backgroundColour = sf::Color::Black;

  _titleText.setFont(_titleFont);
  _titleText.setString("StoryTime");
  _titleText.setCharacterSize(static_cast<uint>(GlobalSettings::WINDOWHEIGHT / 10));
  _titleText.setFillColor(sf::Color::White);
  _titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
  _titleTextRect = _titleText.getLocalBounds();
  _titleText.setOrigin(_titleTextRect.left + _titleTextRect.width / 2.0f, _titleTextRect.top + _titleTextRect.height / 2.0f);
  _titleText.setPosition(sf::Vector2f(static_cast<float>(GlobalSettings::WINDOWWIDTH) / 2.0f, static_cast<float>(GlobalSettings::WINDOWHEIGHT) / 2.0f));
  redraw();
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
  
  return nullptr;
}

void OpeningScreen::draw(sf::RenderWindow& renderWindow)
{
  renderWindow.draw(_titleText);
  drawComplete();
}

sf::Color& OpeningScreen::getBackgroundColour()
{
  return _backgroundColour;
}



} // End namespace StoryTime
