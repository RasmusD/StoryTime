#include "TextHandler.hpp"

namespace StoryTime {

// Constructor
TextHandler::TextHandler(std::string& text)
{
  TextParser::parseText(text, _segments, _choices);

  //std::cout << text << std::endl;
  //std::cout << _choices.size() << std::endl;

  // Set position of core text segment
  _coreText = _segments.front();  
  _segments.pop_front();
  _coreText.getText()->setPosition(10, 10);
  _choiceActive = false;
  /*
  _titleText = TextSegment(_titleFont, "This is the story of a ", 0.05);
  _titleText.getText()->setPosition(10, 10);
  std::vector<std::string> choices = {"man", "woman"};
  _choiceText.getText()->setFillColor(sf::Color::Red);
  sf::Vector2f choicePos = {50, 50};
  //std::cout << "Creating choicebox..." << std::endl;
  _choice = ChoiceBox(_titleFont, choices, choicePos);
  //std::cout << "Done." << std::endl;*/
}

void TextHandler::update(sf::Event& curEvent, sf::Event& prevEvent, sf::Time& elapsedTime)
{
  // If there is an active choice - it takes precedence
  if (_choiceActive == true)
  {
    _currentChoice.update(elapsedTime);
  } else if (_coreText.atEnd == true)
  {
    // Else if we're at the end of the current segment find the next (choice or segment)
    setNextSegment();
  } else {
    // Else update the current segment
    _coreText.update(elapsedTime);
  }
}

void TextHandler::setNextSegment()
{
  if (_choiceActive == false)
  {
    //std::cout << "Here." << std::endl;
    // Activate next choice
    _currentChoice = _choices.front();
    _choices.pop_front();
    _choiceActive = true;
    // Place the next choice
    sf::Vector2f nPos = _coreText.getText()->getPosition();
    nPos.y += _coreText.getText()->getGlobalBounds().height * 2;
    _currentChoice.setPosition(nPos);
    //std::cout << "Here2." << std::endl;
  }
}

void TextHandler::draw(sf::RenderWindow& renderWindow)
{
  _coreText.draw(renderWindow);
  if (_choiceActive == true)
  {
    _currentChoice.draw(renderWindow);
  }
}

} // End namespace StoryTime