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
void ImageBox::update(sf::Time& elapsedTime, std::unordered_set<std::string>& choiceHistory)
{

}

// Draw the box
void ImageBox::draw(sf::RenderWindow& renderWindow, std::unordered_set<std::string>& choiceHistory)
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
    this->_image->setPosition(this->_baseRect.left, this->_baseRect.top);
    sf::Vector2u imageSize = newImage->getSize();
    sf::Vector2f spriteScale = {this->_baseRect.width / (float)imageSize.x,
                                this->_baseRect.height / (float)imageSize.y};
    this->_image->setScale(spriteScale);
  } else {
    this->_image.reset();
  }

  redraw();
}


} // End namespace StoryTime
