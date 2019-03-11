// An image box

// Include guard
#ifndef __ImageBox_H_INCLUDED__
#define __ImageBox_H_INCLUDED__

#include <SFML/Graphics.hpp>

#include "Box.hpp"

namespace StoryTime {

class ImageBox : public Box
{
  public:
    // Constructor
    ImageBox(sf::IntRect boxRect);

    // Destructor
    ~ImageBox() {};

    // Overridden methods
    // React to input
    void takeInput(sf::Event& curEvent, std::unordered_set<std::string>& choiceHistory) override;

    // Update the box
    void update(sf::Time& elapsedTime, std::unordered_set<std::string>& choiceHistory) override;

    // Draw the box
    void draw(sf::RenderWindow& renderWindow, std::unordered_set<std::string>& choiceHistory) override;

    // Inherited methods
    // Set position of the box relative to the top left corner
    // virtual void setPosition(sf::Vector2f newPos);
  private:

    // Inherited methods
    // The box rect
    //sf::IntRect _baseRect;
};


} // End namespace StoryTime


#endif // __ImageBox_H_INCLUDED__;
