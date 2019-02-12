#include "TextBox.hpp"

namespace StoryTime {

// Constructor
TextBox::TextBox(std::unordered_map<std::string, std::string>& storyData,
                        std::unordered_set<std::string>& choiceHistory,
                        std::string& startSegment,
                        Markup& defaultMarkup)
{
  _storyData = storyData;
  _defaultMarkup = defaultMarkup;
  _choiceHistory = choiceHistory;
  _currentSegmentId = startSegment;
  //std::cout << _storyData["[begin]"] << std::endl;
  TextParser::parseText(_storyData[startSegment], _segmentQueue, _defaultMarkup);

  //std::cout << text << std::endl;
  //std::cout << _choices.size() << std::endl;

  _baseX = GlobalSettings::WINDOWWIDTH / 50;
  _baseY = GlobalSettings::WINDOWHEIGHT / 50;

  // Set position of core text segment
  if (_segmentQueue.front().text)
  {
    _screenText.push_back(std::move(_segmentQueue.front().text));
    _screenText.back()->getText().setPosition(_baseX, _baseY);
    _choiceActive = false;
  } else if (_segmentQueue.front().choice) {
    _currentChoice = std::move(_segmentQueue.front().choice);
    sf::Vector2f pos(_baseX, _baseY);
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

void TextBox::takeInput(sf::Event& curEvent)
{
  switch (curEvent.type)
  {
    case sf::Event::KeyPressed:
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2))
      {
        std::filesystem::path quicksavepath = GlobalSettings::SAVEDIR;
        quicksavepath /= "quick.save";
        GameSaver::saveGame(quicksavepath, _choiceHistory, _storyData, _currentSegmentId, true);
        break;
      }
    default:
      if (_choiceActive == true)
      {
        _currentChoice->takeInput(curEvent, _choiceHistory);
      }
      break;
  }
}

void TextBox::update(sf::Time& elapsedTime)
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
        _segmentQueue.front().text->resetText();
        //std::cout << "check" << std::endl;
        setNextSegment();
        //std::cout << "check" << std::endl;
      } else {
        _segmentQueue.push_front(Utils::SegChoice());
        //std::cout << "check" << std::endl;
        _segmentQueue.front().text = std::move(_currentChoice->getChoiceText());
        _segmentQueue.front().text->resetText();
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
        _currentSegmentId = cId;
      }
    }
  } else {
    // Update the current segment
    // First check if a new segment should be grabbed
    if (_screenText.back()->atEnd == true)
    {
      //std::cout << "Setting next segmetn." << std::endl;
      setNextSegment();
    }
    //std::cout << "Updating text." << std::endl;
    // Update it
    _screenText.back()->update(elapsedTime, _choiceHistory);
    // Check if the current segment is beyond the screen and a new line made
    sf::FloatRect bounds = _screenText.back()->getText().getGlobalBounds();
    //std::cout << GlobalSettings::WINDOWWIDTH << " bounds: " << bounds.left + bounds.width << std::endl;
    if (bounds.left + bounds.width >= GlobalSettings::WINDOWWIDTH - _baseX)
    {
      // If it is
      // Create a new segment. One line down
      _screenText.push_back(_screenText.back()->getRemainingTextSegment());
      //std::cout << "Making new line at x: " << _baseX;
      //std::cout << " and y: " << _screenText.back()->getText().getPosition().y + GlobalSettings::getLineSpacing() << std::endl;
      _screenText.back()->getText().setPosition(_baseX, _screenText.back()->getText().getPosition().y + GlobalSettings::getLineSpacing());
      // Update bounds
      bounds = _screenText.back()->getText().getGlobalBounds();
    }
    // Check if lines should move up
    if (bounds.top + bounds.height >= GlobalSettings::WINDOWHEIGHT)
    {
      moveTextLineUp(bounds);
    }
  }
}

void TextBox::setNextSegment()
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

void TextBox::setTextNext()
{ 
  // Set position of next segment
  sf::Vector2f sPos = _screenText.back()->getText().getPosition();;
  if (((std::string)_screenText.back()->getText().getString()).back() == '\n')
  {
    sPos.x = _baseX;
    sPos.y += GlobalSettings::getLineSpacing();
  } else {
    sPos.x += _screenText.back()->getText().getLocalBounds().width;
  }
  _segmentQueue.front().text->getText().setPosition(sPos);
  _screenText.push_back(std::move(_segmentQueue.front().text));
  _segmentQueue.pop_front();
  //std::cout << "push" << std::endl;
}

void TextBox::setChoiceNext()
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

void TextBox::draw(sf::RenderWindow& renderWindow)
{
  //std::cout << "Drwaing..." << std::endl;
  for (auto& segment : _screenText)
  {
    //std::cout << "Drwaing seg..." << std::endl;
    //segment->printTargetText();
    //segment->printVisibleText();
    segment->draw(renderWindow);
    //std::cout << "Done." << std::endl;
  }
  if (_choiceActive == true)
  {
    //std::cout << "Drwaing choice..." << std::endl;
    _currentChoice->draw(renderWindow, _choiceHistory);
  }
}

void TextBox::addBranch(std::string& id)
{
  // Check id exists
  auto it = _storyData.find(id);
  if (it != _storyData.end())
  {
    // Add a new line
    it->second = '\n' + it->second;
    TextParser::parseText(it->second, _segmentQueue, _defaultMarkup);
  } else {
    throw std::runtime_error("Branch not found! Check id - " + id + " - for existence!");
  }
}

sf::Color& TextBox::getBackgroundColour()
{
  if (_choiceActive == true)
  {
    return _currentChoice->getBackgroundColour();
  } else {
    return _screenText.back()->getBackgroundColour();
  }
}

void TextBox::moveTextLineUp(sf::FloatRect& bounds)
{
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