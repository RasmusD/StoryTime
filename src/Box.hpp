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
    virtual ~Box() {};

    // Set position of the box relative to the top left corner
    virtual void setPosition(sf::Vector2i newPos);

    // Set the base box rectangle
    virtual void setBoxRect(sf::IntRect newRect);

    // React to input
    virtual void takeInput(sf::Event& curEvent, std::unordered_set<std::string>& choiceHistory) = 0;

    // Update the box
    virtual void update(sf::Time& elapsedTime, std::unordered_set<std::string>& choiceHistory) = 0;

    // Draw the box
    virtual void draw(sf::RenderWindow& renderWindow, std::unordered_set<std::string>& choiceHistory) = 0;

    // Request a redraw of the box. Subclasses should call this when the graphics change
    void redraw();

    // Indicate to the box that drawing has completed. Subclasses should call this
    // after drawing has finished (in the draw function).
    void drawComplete();

    // Indicates whether the box needs a redraw
    bool needsDraw();

  protected:
    // The box rect
    sf::IntRect _baseRect;

  private:
    bool _needsDraw;
};


} // End namespace StoryTime


#endif // __Box_H_INCLUDED__;
