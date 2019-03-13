#include "ImageBox.hpp"

namespace StoryTime {

// Constructor
ImageBox::ImageBox(sf::IntRect boxRect,
                  const sf::Image* image)
                  : Box(boxRect)
{
  _baseRect = boxRect;
  this->setImage(image);
}

// React to input
void ImageBox::takeInput(sf::Event& curEvent, std::unordered_set<std::string>& choiceHistory)
{

}

// Update the box
void ImageBox::update(sf::Time& elapsedTime, std::unordered_set<std::string>& choiceHistory)
{

}

// Draw the box
void ImageBox::draw(sf::RenderWindow& renderWindow, std::unordered_set<std::string>& choiceHistory)
{
  renderWindow.draw(*_image.get());
  drawComplete();
}

// Change the image in the box
void ImageBox::setImage(const sf::Image* newImage)
{
  if (newImage != nullptr)
  {
    if (_image.get() == nullptr)
    {
      _image = std::unique_ptr<sf::Sprite>(new sf::Sprite());
    }
    sf::Texture texture;
    texture.loadFromImage(*newImage);
    _image->setTexture(texture);
    _image->setTextureRect(_baseRect);
    _image->setPosition(_baseRect.left, _baseRect.top);
  } else {
    _image.reset();
  }

  redraw();
}


} // End namespace StoryTime
