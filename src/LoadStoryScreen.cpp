#include "LoadStoryScreen.hpp"

namespace StoryTime {

LoadStoryScreen::LoadStoryScreen() : GameSlice()
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
  _windowBorder.setScale(static_cast<float>(GlobalSettings::WINDOWWIDTH) / orgSize.x, static_cast<float>(GlobalSettings::WINDOWHEIGHT) / orgSize.y);

  int count = 1;
  for (auto& story : std::filesystem::directory_iterator("saves"))
  {
    sf::Text storyText(story.path().stem().string(), GlobalSettings::DEFAULTFONT, static_cast<uint>(static_cast<float>(GlobalSettings::WINDOWHEIGHT) / static_cast<float>(GlobalSettings::getCharSize()) * 1.5f));
    storyText.setFillColor(sf::Color::White);
    sf::FloatRect textRect = storyText.getLocalBounds();
    storyText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    storyText.setPosition(sf::Vector2f(static_cast<float>(GlobalSettings::WINDOWWIDTH) / 2.0f, static_cast<float>(GlobalSettings::WINDOWHEIGHT) / 4.0f * static_cast<float>(1 + count * 0.4)));
    _storyChoices.push_back(storyText);
    count++;
  }

  _titleText.setFont(GlobalSettings::DEFAULTFONT);
  _titleText.setString("Select A Story To Load");
  _titleText.setCharacterSize(static_cast<uint>(GlobalSettings::WINDOWHEIGHT / GlobalSettings::getCharSize() * 3));
  _titleText.setFillColor(sf::Color::White);
  _titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
  sf::FloatRect textRect = _titleText.getLocalBounds();
  _titleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
  _titleText.setPosition(sf::Vector2f(static_cast<float>(GlobalSettings::WINDOWWIDTH) / 2.0f, static_cast<float>(GlobalSettings::WINDOWHEIGHT) / 4.0f));

  _backgroundColour = sf::Color::Black;
  _changeSlice = false;
  redraw();
}

LoadStoryScreen::~LoadStoryScreen()
{

}

void LoadStoryScreen::takeInput(sf::Event& curEvent, sf::RenderWindow& renderWindow)
{
  //std::cout << "update" << std::endl;
  switch (curEvent.type)
  {
    case sf::Event::MouseButtonReleased:
      for (auto& story : _storyChoices)
      {
        if (story.getGlobalBounds().contains(Utils::toVector2<float>(sf::Mouse::getPosition(renderWindow))) )
        {
          _storyPath = GlobalSettings::ROOTDIR;
          _storyPath /= "saves";
          _storyPath /= std::string(story.getString());
          _storyPath.replace_extension(".save");
          _changeSlice = true;
        }
      }
      break;
    default:
      break;
  }
}

GameSlice* LoadStoryScreen::update(sf::Time& elapsedTime, sf::RenderWindow& renderWindow)
{
  if (_changeSlice == true)
  {
    return new StoryHandler(_storyPath, true);
  }

  return nullptr;
}

sf::Color& LoadStoryScreen::getBackgroundColour()
{
  return _backgroundColour;
}

void LoadStoryScreen::draw(sf::RenderWindow& renderWindow)
{  
  renderWindow.draw(_windowBorder);
  renderWindow.draw(_titleText);
  for (auto& text : _storyChoices)
  {
    renderWindow.draw(text);
  }
  drawComplete();
}


} // End namespace StoryTime
