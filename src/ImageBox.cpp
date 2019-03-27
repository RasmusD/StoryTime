#include "ImageBox.hpp"

namespace StoryTime {

// Constructor
ImageBox::ImageBox(sf::IntRect boxRect,
                  const sf::Texture* image)
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
void ImageBox::update(sf::Time& elapsedTime, const std::unordered_set<std::string>& choiceHistory)
{

}

// Draw the box
void ImageBox::draw(sf::RenderWindow& renderWindow, const std::unordered_set<std::string>& choiceHistory)
{
  if (_image.get() != nullptr)
  {
    renderWindow.draw(*_image.get());
  }
  drawComplete();
}

// Change the image in the box
void ImageBox::setImage(const sf::Texture* newImage)
{
  if (newImage != nullptr)
  {
    if (this->_image.get() == nullptr)
    {
      this->_image = std::unique_ptr<sf::Sprite>(new sf::Sprite());
    }
    this->_image->setTexture(*newImage);
    sf::Vector2u imageSize = newImage->getSize();
    float scale = std::min((float)this->_baseRect.width / (float)imageSize.x,
                      (float)this->_baseRect.height / (float)imageSize.y);
    sf::Vector2f spriteScale = {scale, scale};
    this->_image->setScale(spriteScale);
    this->_image->setPosition(static_cast<float>(this->_baseRect.width) / 2 - static_cast<float>(imageSize.x) * scale / 2,
                              static_cast<float>(this->_baseRect.top));
  } else {
    this->_image.reset();
  }

  redraw();
}


} // End namespace StoryTime
