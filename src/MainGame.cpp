#include "MainGame.hpp"

namespace StoryTime {

MainGame::MainGame() : GameSlice()
{
  // Set font
  if (!GlobalSettings::DEFAULTFONT.loadFromFile("../resources/fonts/rosegarden/Rosegarden.ttf"))
  {
    std::cerr << "Cannot load Rosegarden font!" << std::endl;
    throw;
  }

  // Set border
  if (!_borderTexture.loadFromFile("../resources/textures/border1.png"))
  {
    std::cerr << "Cannot load border texture!" << std::endl;
    throw;
  }
  _windowBorder = sf::Sprite(_borderTexture);
  _windowBorder.setPosition(0, 0);
  sf::Vector2f orgSize = (sf::Vector2f)_borderTexture.getSize();
  _windowBorder.setScale(GlobalSettings::WINDOWWIDTH / orgSize.x, GlobalSettings::WINDOWHEIGHT / orgSize.y);


  // Load and verify the story
  std::unordered_map<std::string, std::string> story;
  if (StoryVerifier::loadAndVerifyStory("../stories/test.story", story, false) == false)
  {
    // TMP
    throw;
  }
  _gameText = std::unique_ptr<TextHandler>(new TextHandler(story));
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

void MainGame::draw(sf::RenderWindow& renderWindow)
{
  renderWindow.draw(_windowBorder);
  //std::cout << "drawing" << std::endl;
  _gameText->draw(renderWindow);
  //std::cout << "drawing end" << std::endl;
}


} // End namespace StoryTime