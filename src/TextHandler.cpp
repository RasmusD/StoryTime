#include "TextHandler.hpp"

namespace StoryTime {

// Constructor
TextHandler::TextHandler(std::string& text)
{
  TextParser::parseText(text, _segmentQueue);

  //std::cout << text << std::endl;
  //std::cout << _choices.size() << std::endl;

  // Set position of core text segment
  _screenText.reserve(_segmentQueue.size());
  if (_segmentQueue.front().text)
  {
    _screenText.push_back(std::move(_segmentQueue.front().text));
    _screenText.back()->getText()->setPosition(10, 10);
    _choiceActive = false;
  } else if (_segmentQueue.front().choice) {
    _currentChoice = std::move(_segmentQueue.front().choice);
    sf::Vector2f pos(10,10);
    _currentChoice->setPosition(pos);
    _choiceActive = true;
  } else {
    throw std::runtime_error("Segment does not have choice or text. What to do?");
  }
  _segmentQueue.pop_front();
  _nLines = 1;
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
    _currentChoice->takeInput(curEvent);
  }
}

void TextHandler::update(sf::Time& elapsedTime)
{
  // If there is an active choice - it takes precedence
  //std::cout << "update" << std::endl;
  if (_choiceActive == true)
  {
    std::cout << "Updating Choice..." << std::endl;
    _currentChoice->update(elapsedTime);
    // If a choice has been made - add the text to screen
    //std::cout << _currentChoice->getChoice() << std::endl;
    if (_currentChoice->getChoice() != -1)
    {
      _segmentQueue.push_front(Utils::SegChoice());
      std::cout << "check" << std::endl;
      _segmentQueue.front().text = std::move(_currentChoice->getChoiceText());
      std::cout << "check" << std::endl;
      setNextSegment();
      std::cout << "check" << std::endl;
    }
  } else if (_screenText.back()->atEnd == true)
  {
    std::cout << "Setting next segmetn." << std::endl;
    setNextSegment();
  } else {
    std::cout << "Updating text." << std::endl;
    // Check if the current segment is beyond the screen
    sf::FloatRect bounds = _screenText.back()->getText()->getGlobalBounds();
    if (bounds.left + bounds.width >= GlobalSettings::WINDOWWIDTH)
    {
      // If it is
      // Create a new segment. One line down
      _screenText.push_back(_screenText.back()->getRemainingTextSegment());
      _screenText.back()->getText()->setPosition(_screenText.front()->getText()->getPosition().x, _screenText.front()->getText()->getPosition().y + bounds.height * (_nLines * 2));
      _nLines++;
    }
    // Else update the current segment
    _screenText.back()->update(elapsedTime);
  }
}

void TextHandler::setNextSegment()
{
  if (_segmentQueue.size() == 0)
  {
    // If we are done
    std::cout << "At end." << std::endl;
  } else if (_segmentQueue.front().text)
  {
    // If we have text in the next segment
    std::cout << "Setting text..." << std::endl;
    setTextNext();
    _choiceActive = false;
  } else if (_segmentQueue.front().choice) {
    std::cout << "Setting choice..." << std::endl;
    // If we have a choice in the next segment
    setChoiceNext();
    _choiceActive = true;
  } else {
    throw std::runtime_error("Next segment does not have either text or choice! What to do?");
  }
}

void TextHandler::setTextNext()
{ 
  // Set position of next segment
  sf::Vector2f sPos = _screenText.back()->getText()->getPosition();
  sPos.x += _screenText.back()->getText()->getLocalBounds().width;
  _segmentQueue.front().text->getText()->setPosition(sPos);
  _screenText.push_back(std::move(_segmentQueue.front().text));
  _segmentQueue.pop_front();
  std::cout << "push" << std::endl;
}

void TextHandler::setChoiceNext()
{
  // Activate next choice
  std::cout << "here" << std::endl;
  /*if (_screenText.size() > 1)
  {
    std::cout << (std::string)_screenText[1]->getText()->getString() << std::endl;
  }*/
  _currentChoice = std::move(_segmentQueue.front().choice);
  /*if (_screenText.size() > 1)
  {
    std::cout << (std::string)_screenText[1]->getText()->getString() << std::endl;
  }*/
  std::cout << "here" << std::endl;
  _segmentQueue.pop_front();
  std::cout << "here" << std::endl;
  // Place the next choice
  sf::Vector2f nPos = _screenText.back()->getText()->getPosition();
  nPos.y += _screenText.back()->getText()->getGlobalBounds().height * 2;
  _currentChoice->setPosition(nPos);
  std::cout << "here" << std::endl;
}

void TextHandler::draw(sf::RenderWindow& renderWindow)
{
  std::cout << "Drwaing..." << std::endl;
  for (auto& segment : _screenText)
  {
    std::cout << "Drwaing seg..." << std::endl;
    segment->printTargetText();
    segment->printVisibleText();
    segment->draw(renderWindow);
    std::cout << "Done." << std::endl;
  }
  if (_choiceActive == true)
  {
    std::cout << "Drwaing choice..." << std::endl;
    _currentChoice->draw(renderWindow);
  }
}

} // End namespace StoryTime