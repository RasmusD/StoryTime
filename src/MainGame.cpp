#include "MainGame.hpp"

namespace StoryTime {

MainGame::MainGame(std::filesystem::path& storyPath, bool storyIsSave) : GameSlice()
{
  // Set border
  std::filesystem::path borderPath = GlobalSettings::ROOTDIR;
  borderPath /= std::filesystem::path("resources/textures/border1.png");
  if (!_borderTexture.loadFromFile(borderPath.string()))
  {
    throw std::runtime_error("Cannot load border texture!");
  }
  _windowBorder = sf::Sprite(_borderTexture);
  _windowBorder.setPosition(0, 0);
  sf::Vector2f orgSize = (sf::Vector2f)_borderTexture.getSize();
  _windowBorder.setScale(GlobalSettings::WINDOWWIDTH / orgSize.x, GlobalSettings::WINDOWHEIGHT / orgSize.y);


  std::unordered_map<std::string, std::string> story;
  std::unordered_set<std::string> choiceHistory;
  std::string startSegment;
  if (storyIsSave == false)
  {
    startSegment = "[begin]";
    // Load and verify the story
    if (StoryVerifier::loadAndVerifyStory(storyPath.string(), story, false, false) == false)
    {
      // TMP
      throw std::runtime_error("Story not valid!");
    }
  } else {
    // Load the save game
    if (GameSaver::loadGame(storyPath, story, choiceHistory, startSegment) == false)
    {
      // TMP
      throw std::runtime_error("Saved story not valid!");
    }
  }
  // Get defaults for this story
  _gameDefaults = Markup();
  if (story.count("[settings]") > 0)
  {
    TextParser::parseSettings(_gameDefaults, story["[settings]"]);
  }
  _gameText = std::unique_ptr<TextBox>(new TextBox(story, choiceHistory, startSegment, _gameDefaults));
}

MainGame::~MainGame()
{

}

void MainGame::takeInput(sf::Event& curEvent, sf::RenderWindow& renderWindow)
{
  //std::cout << "update" << std::endl;
  switch (curEvent.type)
  {
    case sf::Event::MouseButtonReleased:
      _changeSlice = true;
      break;
    default:
      _gameText->takeInput(curEvent);
      break;
  }
}

GameSlice* MainGame::update(sf::Time& elapsedTime, sf::RenderWindow& renderWindow)
{
  _gameText->update(elapsedTime);
  
  //std::cout << "update end" << std::endl;
  return NULL;
}

sf::Color& MainGame::getBackgroundColour()
{
  return _gameText->getBackgroundColour();
}

void MainGame::draw(sf::RenderWindow& renderWindow)
{  
  renderWindow.draw(_windowBorder);
  //std::cout << "drawing" << std::endl;
  _gameText->draw(renderWindow);
  //std::cout << "drawing end" << std::endl;
}


} // End namespace StoryTime