#include "StoryHandler.hpp"

namespace StoryTime {

StoryHandler::StoryHandler(std::filesystem::path& storyPath, bool storyIsSave)
                        : GameSlice(),
                          _storyPath(storyPath)
{
  std::unordered_map<std::string, std::string> story;
  std::unordered_set<std::string> choiceHistory;
  std::string startSegment;
  if (storyIsSave == false)
  {
    startSegment = "[begin]";
    // Load and verify the story
    if (StoryVerifier::loadAndVerifyStory(storyPath, story, _resources, false, false) == false)
    {
      // TMP
      throw std::runtime_error("Story not valid!");
    }
  } else {
    // Load the save game
    if (GameSaver::loadGame(storyPath, _storyPath, _resources, story, choiceHistory, startSegment) == false)
    {
      // TMP
      throw std::runtime_error("Saved story not valid!");
    }
  }
  // Set story
  _storyData = story;
  // Get defaults for this story
  _gameDefaults = Markup();
  if (story.count("[settings]") > 0)
  {
    TextParser::parseSettings(_gameDefaults, _storyData["[settings]"]);
  }

  // Setup choicehistory and start segment
  _choiceHistory = choiceHistory;
  _currentSegmentId = startSegment;
  //std::cout << _storyData["[begin]"] << std::endl;
  TextParser::parseText(_storyData[startSegment], _segmentQueue, _gameDefaults);

  // Set position of core text segment
  std::unique_ptr<TextSegment> startText;
  if (_segmentQueue.front().text)
  {
    startText = std::move(_segmentQueue.front().text);
    _choiceActive = false;
  } else if (_segmentQueue.front().choice) {
    _currentChoice = std::move(_segmentQueue.front().choice);
    _currentChoice->setBoxRect(sf::IntRect(static_cast<int>(static_cast<float>(GlobalSettings::WINDOWWIDTH) * 0.01f),
                                           static_cast<int>(static_cast<float>(GlobalSettings::WINDOWHEIGHT) * 0.80f),
                                           static_cast<int>(static_cast<float>(GlobalSettings::WINDOWWIDTH) * 0.98f),
                                           static_cast<int>(GlobalSettings::WINDOWHEIGHT)));
    _choiceActive = true;
  } else {
    throw std::runtime_error("Segment does not have choice or text. What to do?");
  }
  _segmentQueue.pop_front();

  _gameText = std::unique_ptr<TextBox>(new TextBox(startText, sf::IntRect(static_cast<int>(static_cast<float>(GlobalSettings::WINDOWWIDTH) * 0.01f),
                                                                         static_cast<int>(static_cast<float>(GlobalSettings::WINDOWHEIGHT) * 0.5f),
                                                                         static_cast<int>(static_cast<float>(GlobalSettings::WINDOWWIDTH) * 0.98f),
                                                                         static_cast<int>(static_cast<float>(GlobalSettings::WINDOWHEIGHT) * 0.3f))));

  // Set image box
  if (_gameText->getDisplayImage() == "")
  {
    if (_resources.addImage(storyPath.parent_path(), "testImage.jpg") == false)
    {
      throw std::runtime_error("Cannot load default image.");
    }
    _imageBox = std::unique_ptr<ImageBox>(new ImageBox(sf::IntRect(static_cast<int>(static_cast<float>(GlobalSettings::WINDOWWIDTH) * 0.01),
                         static_cast<int>(static_cast<float>(GlobalSettings::WINDOWHEIGHT) * 0.01f),
                         static_cast<int>(static_cast<float>(GlobalSettings::WINDOWWIDTH) * 0.98f),
                         static_cast<int>(static_cast<float>(GlobalSettings::WINDOWHEIGHT) / 2.f * 0.99f)),
                        _resources.getImagePtr("testImage.jpg")));
  } else {
    _imageBox = std::unique_ptr<ImageBox>(new ImageBox(sf::IntRect(static_cast<int>(static_cast<float>(GlobalSettings::WINDOWWIDTH) * 0.01),
                         static_cast<int>(static_cast<float>(GlobalSettings::WINDOWHEIGHT) * 0.01f),
                         static_cast<int>(static_cast<float>(GlobalSettings::WINDOWWIDTH) * 0.98f),
                         static_cast<int>(static_cast<float>(GlobalSettings::WINDOWHEIGHT) / 2.f * 0.99f)),
                        _resources.getImagePtr(_gameText->getDisplayImage())));
  }

  // Set border
  std::filesystem::path borderPath = GlobalSettings::ROOTDIR;
  borderPath /= std::filesystem::path("resources/textures/border1.png");
  if (!_borderTexture.loadFromFile(borderPath.string()))
  {
    throw std::runtime_error("Cannot load border texture!");
  }
  _windowBorder = sf::Sprite(_borderTexture);
  _windowBorder.setPosition(0, 0);
  sf::Vector2f orgSize = static_cast<sf::Vector2f>(_borderTexture.getSize());
  _windowBorder.setScale(static_cast<float>(GlobalSettings::WINDOWWIDTH) / orgSize.x, static_cast<float>(GlobalSettings::WINDOWHEIGHT) / orgSize.y);
  redraw();
}

StoryHandler::~StoryHandler()
{

}

void StoryHandler::takeInput(sf::Event& curEvent, sf::RenderWindow& renderWindow)
{
  switch (curEvent.type)
  {
    case sf::Event::KeyPressed:
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2))
      {
        std::filesystem::path quicksavepath = GlobalSettings::SAVEDIR;
        quicksavepath /= "quick.save";
        GameSaver::saveGame(quicksavepath, _storyPath, _choiceHistory, _storyData, _currentSegmentId, true);
      }
      // No break
    default:
      if (_choiceActive == true)
      {
        _currentChoice->takeInput(curEvent, _choiceHistory);
      }
      break;
  }
}

GameSlice* StoryHandler::update(sf::Time& elapsedTime, sf::RenderWindow& renderWindow)
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
        _setNextSegment();
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
        _addBranch(cId);
        _setNextSegment();
        _currentSegmentId = cId;
      }
    }
  } else {
    // Update the current segment
    _gameText->update(elapsedTime, _choiceHistory);
    // First check if a new segment should be grabbed
    if (_gameText->atEnd() == true)
    {
      //std::cout << "Setting next segmetn." << std::endl;
      _setNextSegment();
    }
  }

  if (_gameText->needsDraw() || _currentChoice->needsDraw() || _imageBox->needsDraw())
  {
    redraw();
  }

  //std::cout << "update end" << std::endl;
  return nullptr;
}

void StoryHandler::_setNextSegment()
{
  if (_segmentQueue.size() == 0)
  {
    // If we are done
    //std::cout << "At end." << std::endl;
  } else if (_segmentQueue.front().text)
  {
    // If we have text in the next segment
    //std::cout << "Setting text..." << std::endl;
    _setTextNext();
    _choiceActive = false;
  } else if (_segmentQueue.front().choice) {
    //std::cout << "Setting choice..." << std::endl;
    // If we have a choice in the next segment
    _setChoiceNext();
    _choiceActive = true;
  } else {
    throw std::runtime_error("Next segment does not have either text or choice! What to do?");
  }
}

void StoryHandler::_setTextNext()
{
  _gameText->addTextSegment(_segmentQueue.front().text);
  _segmentQueue.pop_front();
  _imageBox->setImage(_resources.getImagePtr(_gameText->getDisplayImage()));
  //std::cout << "push" << std::endl;
}

void StoryHandler::_setChoiceNext()
{
  // Activate next choice
  _currentChoice = std::move(_segmentQueue.front().choice);
  _segmentQueue.pop_front();

  // Place the choice - have to do this every time unfortunately
  _currentChoice->setBoxRect(sf::IntRect(static_cast<int>(static_cast<float>(GlobalSettings::WINDOWWIDTH) * 0.01f),
                                         static_cast<int>(static_cast<float>(GlobalSettings::WINDOWHEIGHT) * 0.80f),
                                         static_cast<int>(static_cast<float>(GlobalSettings::WINDOWWIDTH) * 0.98f),
                                         static_cast<int>(GlobalSettings::WINDOWHEIGHT)));
  _imageBox->setImage(_resources.getImagePtr(_gameText->getDisplayImage()));
}

void StoryHandler::_addBranch(std::string& id)
{
  // Check id exists
  auto it = _storyData.find(id);
  if (it != _storyData.end())
  {
    // Add a new line
    it->second = '\n' + it->second;
    TextParser::parseText(it->second, _segmentQueue, _gameDefaults);
  } else {
    throw std::runtime_error("Branch not found! Check id - " + id + " - for existence!");
  }
}

const sf::Color& StoryHandler::getBackgroundColour()
{
  return _gameText->getBackgroundColour();
}

void StoryHandler::draw(sf::RenderWindow& renderWindow)
{  
  renderWindow.draw(_windowBorder);
  //std::cout << "drawing" << std::endl;
  _gameText->draw(renderWindow, _choiceHistory);
  _imageBox->draw(renderWindow, _choiceHistory);
  //std::cout << "drawing end" << std::endl;
  if (_choiceActive == true)
  {
    //std::cout << "Drwaing choice..." << std::endl;
    _currentChoice->draw(renderWindow, _choiceHistory);
  }

  drawComplete();
}


} // End namespace StoryTime
