#include "Box.hpp"

namespace StoryTime {

// Constructor
Box::Box(sf::IntRect boxRect) :
  _baseRect(boxRect),
  _needsDraw(false)
{
}

void Box::setPosition(sf::Vector2f newPos)
{
  _baseRect.left = newPos.x;
  _baseRect.top = newPos.y;
  redraw();
}

void Box::redraw() { _needsDraw = true; }

void Box::drawComplete() { _needsDraw = false; }

bool Box::needsDraw() { return _needsDraw; }

} // End namespace StoryTime
