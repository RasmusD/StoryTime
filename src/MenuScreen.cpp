#include "MenuScreen.hpp"

namespace StoryTime {

MenuScreen::MenuScreen() : GameSlice()
{
  _titleFont = GlobalSettings::DEFAULTFONT;

  _newGame = false;
  _loadGame = false;

  _titleText.setFont(_titleFont);
  _titleText.setString("Main Menu");
  _titleText.setCharacterSize(static_cast<uint>(static_cast<float>(GlobalSettings::WINDOWHEIGHT) / static_cast<float>(GlobalSettings::getCharSize()) * 3.f));
  _titleText.setFillColor(sf::Color::White);
  _titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
  _textRect = _titleText.getLocalBounds();
  _titleText.setOrigin(_textRect.left + _textRect.width / 2.0f, _textRect.top + _textRect.height / 2.0f);
  _titleText.setPosition(sf::Vector2f(static_cast<float>(GlobalSettings::WINDOWWIDTH) / 2.0f, static_cast<float>(GlobalSettings::WINDOWHEIGHT) / 4.0f));

  _newGameText.setFont(_titleFont);
  _newGameText.setString("Play Game");
  _newGameText.setCharacterSize(static_cast<uint>(static_cast<float>(GlobalSettings::WINDOWHEIGHT) / static_cast<float>(GlobalSettings::getCharSize()) * 3));
  _newGameText.setFillColor(sf::Color::White);
  _newGameText.setStyle(sf::Text::Bold | sf::Text::Underlined);
  _textRect = _newGameText.getLocalBounds();
  _newGameText.setOrigin(_textRect.left + _textRect.width / 2.0f, _textRect.top + _textRect.height / 2.0f);
  _newGameText.setPosition(sf::Vector2f(static_cast<float>(GlobalSettings::WINDOWWIDTH) / 2.0f, static_cast<float>(GlobalSettings::WINDOWHEIGHT) / 2.f));

  _loadGameText.setFont(_titleFont);
  _loadGameText.setString("Load Game");
  _loadGameText.setCharacterSize(static_cast<uint>(static_cast<float>(GlobalSettings::WINDOWHEIGHT) / static_cast<float>(GlobalSettings::getCharSize()) * 3));
  _loadGameText.setFillColor(sf::Color::White);
  _loadGameText.setStyle(sf::Text::Bold | sf::Text::Underlined);
  _textRect = _loadGameText.getLocalBounds();
  _loadGameText.setOrigin(_textRect.left + _textRect.width / 2.0f, _textRect.top + _textRect.height / 2.0f);
  _loadGameText.setPosition(sf::Vector2f(static_cast<float>(GlobalSettings::WINDOWWIDTH) / 2.f, static_cast<float>(GlobalSettings::WINDOWHEIGHT) / 1.25f));

  _backgroundColour = sf::Color::Black;
  redraw();
}

void MenuScreen::takeInput(sf::Event& curEvent, sf::RenderWindow& renderWindow)
{
  switch (curEvent.type)
  {
    case sf::Event::MouseButtonReleased:
      if (_newGameText.getGlobalBounds().contains(Utils::toVector2<float>(sf::Mouse::getPosition(renderWindow))) )
      {
        _newGame = true;
      } else if (_loadGameText.getGlobalBounds().contains(Utils::toVector2<float>(sf::Mouse::getPosition(renderWindow))) )
      {
        _loadGame = true;
      }
      break;
    default:
      break;
  }
}

GameSlice* MenuScreen::update(sf::Time& elapsedTime, sf::RenderWindow& renderWindow)
{
  if (_newGame == true)
  {
    return new SelectStory();
  } else if (_loadGame == true)
  {
    return new LoadStoryScreen();
  }

  return nullptr;
}

void MenuScreen::draw(sf::RenderWindow& renderWindow)
{
  renderWindow.draw(_titleText);
  renderWindow.draw(_newGameText);
  renderWindow.draw(_loadGameText);
  drawComplete();
}

sf::Color& MenuScreen::getBackgroundColour()
{
  return _backgroundColour;
}

} // End namespace Story
