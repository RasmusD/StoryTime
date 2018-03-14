#include "TextHandler.hpp"

namespace StoryTime {

// Constructor
TextHandler::TextHandler(std::unordered_map<std::string, std::string>& storyData)
{
  _storyData = storyData;
  //std::cout << _storyData["[begin]"] << std::endl;
  TextParser::parseText(_storyData["[begin]"], _segmentQueue);

  //std::cout << text << std::endl;
  //std::cout << _choices.size() << std::endl;

  // Set position of core text segment
  if (_segmentQueue.front().text)
  {
    _screenText.push_back(std::move(_segmentQueue.front().text));
    _screenText.back()->getText().setPosition(10, 10);
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
  /*
  _titleText = TextSegment(_titleFont, "This is the story of a ", 0.05);
  _titleText.getText().setPosition(10, 10);
  std::vector<std::string> choices = {"man", "woman"};
  _choiceText.getText().setFillColor(sf::Color::Red);
  sf::Vector2f choicePos = {50, 50};
  //std::cout << "Creating choicebox..." << std::endl;
  _choice = ChoiceBox(_titleFont, choices, choicePos);
  //std::cout << "Done." << std::endl;*/
}

void TextHandler::takeInput(sf::Event& curEvent)
{
  if (_choiceActive == true)
  {
    _currentChoice->takeInput(curEvent, _choiceHistory);
  }
}

void TextHandler::update(sf::Time& elapsedTime)
{
  // If there is an active choice - it takes precedence
  //std::cout << "update" << std::endl;
  if (_choiceActive == true)
  {
    //std::cout << "Updating Choice..." << std::endl;
    _currentChoice->update(elapsedTime, _choiceHistory);
    // If a choice has been made - add the text to screen
    //std::cout << _currentChoice->getChoiceId() << std::endl;
    if (_currentChoice->getChoiceId() != "")
    {
      // If this is a simple continue choice - continue
      if (_currentChoice->getChoiceId() == "<continue>")
      {
        _segmentQueue.push_front(Utils::SegChoice());
        //std::cout << "check" << std::endl;
        _segmentQueue.front().text = std::move(_currentChoice->getChoiceText());
        //std::cout << "check" << std::endl;
        setNextSegment();
        //std::cout << "check" << std::endl;
      } else {
        _segmentQueue.push_front(Utils::SegChoice());
        //std::cout << "check" << std::endl;
        _segmentQueue.front().text = std::move(_currentChoice->getChoiceText());
        // Add a whitespace at the end of this if necessary
        //std::cout << (std::string)_segmentQueue.back().text->getText().getString() << std::endl;
        if (std::string(_segmentQueue.back().text->getText().getString()).back() != ' ')
        {
          std::string space(" ");
          _segmentQueue.back().text->addText(space);
        }
        //std::cout << "check" << std::endl;
        // Expand the queue with the chosen branch
        std::string cId = _currentChoice->getChoiceId();
        addBranch(cId);
        setNextSegment();
      }
    }
  } else if (_screenText.back()->atEnd == true)
  {
    //std::cout << "Setting next segmetn." << std::endl;
    setNextSegment();
  } else {
    //std::cout << "Updating text." << std::endl;
    // Check if the current segment is beyond the screen
    sf::FloatRect bounds = _screenText.back()->getText().getGlobalBounds();
    // Check if lines should move up
    if (bounds.top + bounds.height >= GlobalSettings::WINDOWHEIGHT)
    {
      moveTextLineUp();
    }
    // Check if new line should be made
    if (bounds.left + bounds.width >= GlobalSettings::WINDOWWIDTH)
    {
      // If it is
      // Create a new segment. One line down
      _screenText.push_back(_screenText.back()->getRemainingTextSegment());
      _screenText.back()->getText().setPosition(_screenText.front()->getText().getPosition().x, _screenText.back()->getText().getPosition().y + GlobalSettings::getLineSpacing());
    }
    // Else update the current segment
    _screenText.back()->update(elapsedTime, _choiceHistory);
  }
}

void TextHandler::setNextSegment()
{
  if (_segmentQueue.size() == 0)
  {
    // If we are done
    //std::cout << "At end." << std::endl;
  } else if (_segmentQueue.front().text)
  {
    // If we have text in the next segment
    //std::cout << "Setting text..." << std::endl;
    setTextNext();
    _choiceActive = false;
  } else if (_segmentQueue.front().choice) {
    //std::cout << "Setting choice..." << std::endl;
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
  sf::Vector2f sPos = _screenText.back()->getText().getPosition();;
  if (((std::string)_screenText.back()->getText().getString()).back() == '\n')
  {
    // Front segment guaranteed to have correct x
    sPos.x = _screenText.front()->getText().getPosition().x;
    sPos.y += GlobalSettings::getLineSpacing();
  } else {
    sPos.x += _screenText.back()->getText().getLocalBounds().width;
  }
  _segmentQueue.front().text->getText().setPosition(sPos);
  _screenText.push_back(std::move(_segmentQueue.front().text));
  _segmentQueue.pop_front();
  //std::cout << "push" << std::endl;
}

void TextHandler::setChoiceNext()
{
  // Activate next choice
  //std::cout << "here" << std::endl;
  /*if (_screenText.size() > 1)
  {
    //std::cout << (std::string)_screenText[1]->getText().getString() << std::endl;
  }*/
  _currentChoice = std::move(_segmentQueue.front().choice);
  /*if (_screenText.size() > 1)
  {
    //std::cout << (std::string)_screenText[1]->getText().getString() << std::endl;
  }*/
  //std::cout << "here" << std::endl;
  _segmentQueue.pop_front();
  //std::cout << "here" << std::endl;
  // Place the next choice
  sf::Vector2f nPos = _screenText.back()->getText().getPosition();
  nPos.y += GlobalSettings::getLineSpacing();
  _currentChoice->setPosition(nPos);
  //std::cout << "here" << std::endl;
}

void TextHandler::draw(sf::RenderWindow& renderWindow)
{
  //std::cout << "Drwaing..." << std::endl;
  for (auto& segment : _screenText)
  {
    //std::cout << "Drwaing seg..." << std::endl;
    segment->printTargetText();
    segment->printVisibleText();
    segment->draw(renderWindow);
    //std::cout << "Done." << std::endl;
  }
  if (_choiceActive == true)
  {
    //std::cout << "Drwaing choice..." << std::endl;
    _currentChoice->draw(renderWindow, _choiceHistory);
  }
}

void TextHandler::addBranch(std::string& id)
{
  // Check id exists
  auto it = _storyData.find(id);
  if (it != _storyData.end())
  {
    // Add a new line
    it->second = '\n' + it->second;
    TextParser::parseText(it->second, _segmentQueue);
  } else {
    throw std::runtime_error("Branch not found! Check id - " + id + " - for existence!");
  }
}

void TextHandler::moveTextLineUp()
{
  // Current top
  sf::FloatRect bounds = _screenText.front()->getText().getLocalBounds();
  // Move elements up by height
  sf::Vector2f pos;
  for (auto& seg : _screenText)
  {
    pos = seg->getText().getPosition();
    seg->getText().setPosition(pos.x, pos.y - GlobalSettings::getLineSpacing());
  }
  // Get rid of all the obsolete elements
  // We assume height is valid
  while (_screenText.front()->getText().getGlobalBounds().top + bounds.height <= 0)
  {
    _screenText.pop_front();
  }
}

} // End namespace StoryTime