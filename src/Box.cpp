#include "Box.hpp"

namespace StoryTime {

// Constructor
Box::Box(sf::IntRect boxRect) :
  _baseRect(boxRect)
{
}

void Box::setPosition(sf::Vector2i newPos)
{
  _baseRect.left = newPos.x;
  _baseRect.top = newPos.y;
  redraw();
}

void Box::setBoxRect(sf::IntRect newRect)
{
  _baseRect = newRect;
  redraw();
}

void Box::redraw() { _needsDraw = true; }

void Box::drawComplete() { _needsDraw = false; }

const bool Box::needsDraw() { return _needsDraw; }

} // End namespace StoryTime
