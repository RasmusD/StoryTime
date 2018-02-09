#include "TextHandler.hpp"

namespace StoryTime {

// Constructor
TextHandler::TextHandler(std::string& text)
{
  TextParser::parseText(text, _segments, _choices);

  //std::cout << text << std::endl;
  //std::cout << _choices.size() << std::endl;

  // Set position of core text segment
  _coreText.reserve(_segments.size() + _choices.size());
  _coreText.push_back(_segments.front());  
  _segments.pop_front();
  _coreText.back().getText()->setPosition(10, 10);
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

void TextHandler::takeInput(sf::Event& curEvent)
{
  if (_choiceActive == true)
  {
    _currentChoice.takeInput(curEvent);
  }
}

void TextHandler::update(sf::Time& elapsedTime)
{
  // If there is an active choice - it takes precedence
  if (_choiceActive == true)
  {
    _currentChoice.update(elapsedTime);
    // If a choice has been made
    if (_currentChoice.getChoice() != -1)
    {
      setNextSegment();
    }
  } else if (_coreText.back().atEnd == true)
  {
    // Else if we're at the end of the current segment find the next (choice or segment)
    setNextSegment();
  } else {
    //std::cout << "Updating text." << std::endl;
    // Else update the current segment
    for (auto& segment : _coreText)
    {
      segment.update(elapsedTime);
    }
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
    sf::Vector2f nPos = _coreText.back().getText()->getPosition();
    nPos.y += _coreText.back().getText()->getGlobalBounds().height * 2;
    _currentChoice.setPosition(nPos);
    //std::cout << "Here2." << std::endl;
  } else if (_segments.size() > 0) {
    // Set position of next segment
    sf::Vector2f sPos = _coreText.back().getText()->getPosition();
    sPos.x += _coreText.back().getText()->getLocalBounds().width + _coreText.back().getText()->getFont()->getGlyph(0020, _segments.front().getText()->getCharacterSize(), false).advance;
    _segments.front().getText()->setPosition(sPos);
    _coreText.push_back(_segments.front());
    _segments.pop_front();
    _choiceActive = false;
  } else {
    std::cout << "At end." << std::endl;
  }
}

void TextHandler::draw(sf::RenderWindow& renderWindow)
{
  for (auto& segment : _coreText)
  {
    //segment.printTargetText();
    //segment.printVisibleText();
    segment.draw(renderWindow);
  }
  if (_choiceActive == true)
  {
    _currentChoice.draw(renderWindow);
  }
}

} // End namespace StoryTime