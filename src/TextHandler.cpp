#include "TextHandler.hpp"

namespace StoryTime {

// Constructor
TextHandler::TextHandler(std::string& text)
{
  TextParser::parseText(text, _segments, _choices);

  //std::cout << text << std::endl;
  //std::cout << _choices.size() << std::endl;

  // Set position of core text segment
  _screenText.reserve(_segments.size() + _choices.size());
  _screenText.push_back(_segments.front());  
  _segments.pop_front();
  _screenText.back().getText()->setPosition(10, 10);
  _choiceActive = false;
  _isNextChoice = true;
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
    //std::cout << _currentChoice.getChoice() << std::endl;
    if (_currentChoice.getChoice() != -1)
    {
      _segments.push_front(_currentChoice.getChoiceText());
      setNextSegment();
      _isNextChoice = false;
    }
  } else if (_screenText.back().atEnd == true)
  {
    //std::cout << "Setting segment..." << std::endl;
    // Else if we're at the end of the current segment find the next (choice or segment)
    setNextSegment();
    if (_choices.size() > 0)
    {
      _isNextChoice = true;
    }
  } else {
    //std::cout << "Updating text." << std::endl;
    // Check if the current segment is beyond the screen
    sf::FloatRect bounds = _screenText.back().getText()->getGlobalBounds();
    if (bounds.left + bounds.width >= GlobalSettings::WINDOWWIDTH)
    {
      // If it is
      // Create a new segment. One line down
      _screenText.push_back(_screenText.back().getRemainingTextSegment());
      _screenText.back().getText()->setPosition(_screenText.front().getText()->getPosition().x, _screenText.front().getText()->getPosition().y + bounds.height * 2);
    }
    // Else update the current segment
    _screenText.back().update(elapsedTime);
  }
}

void TextHandler::setNextSegment()
{
  //std::cout << "Setting segment." << std::endl;
  if (_isNextChoice == true && _choices.size() > 0)
  {
    setChoiceNext();
    _choiceActive = true;
  } else if (_segments.size() > 0) {
    setTextNext();
    _choiceActive = false;
  } else {
    std::cout << "At end." << std::endl;
  }
}

void TextHandler::setTextNext()
{ 
  // Set position of next segment
  sf::Vector2f sPos = _screenText.back().getText()->getPosition();
  sPos.x += _screenText.back().getText()->getLocalBounds().width;
  _segments.front().getText()->setPosition(sPos);
  _screenText.push_back(_segments.front());
  _segments.pop_front();
}

void TextHandler::setChoiceNext()
{
  //std::cout << "Here." << std::endl;
  // Activate next choice
  _currentChoice = _choices.front();
  _choices.pop_front();
  _choiceActive = true;
  // Place the next choice
  sf::Vector2f nPos = _screenText.back().getText()->getPosition();
  nPos.y += _screenText.back().getText()->getGlobalBounds().height * 2;
  _currentChoice.setPosition(nPos);
  //std::cout << "Here2." << std::endl;
}

void TextHandler::draw(sf::RenderWindow& renderWindow)
{
  for (auto& segment : _screenText)
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