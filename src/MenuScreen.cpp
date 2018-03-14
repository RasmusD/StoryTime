#include "MenuScreen.hpp"

namespace StoryTime {

MenuScreen::MenuScreen() : GameSlice()
{
  if (!_titleFont.loadFromFile("../resources/fonts/rosegarden/Rosegarden.ttf"))
  {
    std::cerr << "Cannot load Rosegarden font!" << std::endl;
    throw;
  }

  _changeSlice = false;

  _titleText.setFont(_titleFont);
  _titleText.setString("Main Menu");
  _titleText.setCharacterSize(GlobalSettings::WINDOWHEIGHT / (GlobalSettings::getCharSize() / 3));
  _titleText.setFillColor(sf::Color::White);
  _titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
  _textRect = _titleText.getLocalBounds();
  _titleText.setOrigin(_textRect.left + _textRect.width / 2.0f, _textRect.top + _textRect.height / 2.0f);
  _titleText.setPosition(sf::Vector2f(GlobalSettings::WINDOWWIDTH / 2.0f, GlobalSettings::WINDOWHEIGHT / 4.0f));

  _newgameText.setFont(_titleFont);
  _newgameText.setString("Play Game");
  _newgameText.setCharacterSize(GlobalSettings::WINDOWHEIGHT / (GlobalSettings::getCharSize() / 3));
  _newgameText.setFillColor(sf::Color::White);
  _newgameText.setStyle(sf::Text::Bold | sf::Text::Underlined);
  _textRect = _newgameText.getLocalBounds();
  _newgameText.setOrigin(_textRect.left + _textRect.width / 2.0f, _textRect.top + _textRect.height / 2.0f);
  _newgameText.setPosition(sf::Vector2f(GlobalSettings::WINDOWWIDTH / 2.0f, GlobalSettings::WINDOWHEIGHT / 1.5f));
}

void MenuScreen::takeInput(sf::Event& curEvent, sf::RenderWindow& renderWindow)
{
  switch (curEvent.type)
  {
    case sf::Event::MouseButtonReleased:
      if (_newgameText.getGlobalBounds().contains(Utils::toVector2<float>(sf::Mouse::getPosition(renderWindow))) )
      {
        _changeSlice = true;
      }
      break;
    default:
      break;
  }
}

GameSlice* MenuScreen::update(sf::Time& elapsedTime, sf::RenderWindow& renderWindow)
{
  if (_changeSlice == true)
  {
    return new MainGame();
  }

  return NULL;
}

void MenuScreen::draw(sf::RenderWindow& renderWindow)
{
  renderWindow.draw(_titleText);
  renderWindow.draw(_newgameText);
}

} // End namespace Story