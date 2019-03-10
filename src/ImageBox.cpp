#include "ImageBox.hpp"

namespace StoryTime {

// Constructor
ImageBox::ImageBox(sf::IntRect boxRect
                  )
                  : Box(boxRect)
{
  _baseRect = boxRect;
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

}


} // End namespace StoryTime