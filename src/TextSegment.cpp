#include "TextSegment.hpp"

namespace StoryTime {

// Constructor
TextSegment::TextSegment(const sf::Font& font, std::string text, float drawSpeed)
{
  _text.setString("");
  _text.setCharacterSize(GlobalSettings::WINDOWHEIGHT / GlobalSettings::CHARSIZE);
  _text.setFillColor(sf::Color::White);
  _text.setFont(font);

  _drawSpeed = drawSpeed;
  _targetText = text;
  atEnd = false;
}

TextSegment::TextSegment()
{
  // Do nothing
}

sf::Text* TextSegment::getText()
{
  return &_text;
}

void TextSegment::update(sf::Time& elapsedTime)
{
  if (atEnd == false)
  {
    //std::cout << "Not at end" << std::endl;
    // Will only occur once
    if (_drawSpeed < 0)
    {
      _text.setString(_targetText);
      atEnd = true;
      return;
    }
    _timeCount += elapsedTime.asSeconds();
    while (_timeCount > _drawSpeed)
    {
      _text.setString(_targetText.substr(0, _stringPos));
      _timeCount -= _drawSpeed;
      if (_stringPos == _targetText.size())
      {
        atEnd = true;
        return;
      }
      _stringPos++;
    }
  }
}

void TextSegment::draw(sf::RenderWindow& renderWindow)
{
  renderWindow.draw(_text);
}

sf::FloatRect TextSegment::getLocalBounds()
{
  // Simulate the full length
  _text.setString(_targetText);
  // Get the width of that
  sf::FloatRect bounds = _text.getLocalBounds();
  // Set the string back to current position
  _text.setString(_targetText.substr(0, _stringPos));
  return bounds;
}

void TextSegment::printTargetText()
{
  std::cout << _targetText << std::endl;
}

void TextSegment::printVisibleText()
{
  std::cout << (std::string)_text.getString() << std::endl;
}

void TextSegment::addText(std::string& toAdd)
{
  _targetText += toAdd;
  atEnd = false;
}

} // End namespace StoryTime