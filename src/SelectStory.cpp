#include "SelectStory.hpp"

namespace StoryTime {

SelectStory::SelectStory() : GameSlice()
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

  _storyPath = GlobalSettings::ROOTDIR;
  _storyPath /= std::filesystem::path("stories/test.story");

  _titleText.setFont(GlobalSettings::DEFAULTFONT);
  _titleText.setString("Main Menu");
  _titleText.setCharacterSize(GlobalSettings::WINDOWHEIGHT / (GlobalSettings::getCharSize() / 3));
  _titleText.setFillColor(sf::Color::White);
  _titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
  sf::FloatRect textRect = _titleText.getLocalBounds();
  _titleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
  _titleText.setPosition(sf::Vector2f(GlobalSettings::WINDOWWIDTH / 2.0f, GlobalSettings::WINDOWHEIGHT / 4.0f));

  _backgroundColour = sf::Color::Black;
}

SelectStory::~SelectStory()
{

}

void SelectStory::takeInput(sf::Event& curEvent, sf::RenderWindow& renderWindow)
{
  //std::cout << "update" << std::endl;
  switch (curEvent.type)
  {
    case sf::Event::MouseButtonReleased:
      _changeSlice = true;
      break;
    default:
      break;
  }
}

GameSlice* SelectStory::update(sf::Time& elapsedTime, sf::RenderWindow& renderWindow)
{
  if (_changeSlice == true)
  {
    return new MainGame(_storyPath);
  }

  return NULL;
}

sf::Color& SelectStory::getBackgroundColour()
{
  return _backgroundColour;
}

void SelectStory::draw(sf::RenderWindow& renderWindow)
{  
  renderWindow.draw(_windowBorder);
  renderWindow.draw(_titleText);
}


} // End namespace StoryTime