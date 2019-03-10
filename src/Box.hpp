// Abstract base class for all boxes

// Include guard
#ifndef __Box_H_INCLUDED__
#define __Box_H_INCLUDED__

#include <unordered_set>

#include <SFML/Graphics.hpp>

namespace StoryTime {

class Box
{
  public:
    // Constructor
    Box(sf::IntRect boxRect);

    // Destructor
    ~Box() {};

    // Set position of the box relative to the top left corner
    virtual void setPosition(sf::Vector2f newPos);

    // React to input
    virtual void takeInput(sf::Event& curEvent, std::unordered_set<std::string>& choiceHistory) = 0;

    // Update the box
    virtual void update(sf::Time& elapsedTime, std::unordered_set<std::string>& choiceHistory) = 0;

    // Draw the box
    virtual void draw(sf::RenderWindow& renderWindow, std::unordered_set<std::string>& choiceHistory) = 0;

  protected:
    // The box rect
    sf::IntRect _baseRect;
};


} // End namespace StoryTime


#endif // __Box_H_INCLUDED__;