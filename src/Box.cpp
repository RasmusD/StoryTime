#include "Box.hpp"

namespace StoryTime {

// Constructor
Box::Box(sf::IntRect boxRect)
{
  _baseRect = boxRect;
}

void Box::setPosition(sf::Vector2f newPos)
{
  _baseRect.left = newPos.x;
  _baseRect.top = newPos.y;
}

} // End namespace StoryTime