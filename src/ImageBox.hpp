// An image box

// Include guard
#ifndef __ImageBox_H_INCLUDED__
#define __ImageBox_H_INCLUDED__

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Box.hpp"

namespace StoryTime {

class ImageBox : public Box
{
  public:
    // Constructor
    ImageBox(sf::IntRect boxRect, const sf::Texture* image);

    // Destructor
    ~ImageBox() {};

    // Overridden methods
    // React to input
    void takeInput(sf::Event& curEvent, std::unordered_set<std::string>& choiceHistory) override;

    // Update the box
    void update(sf::Time& elapsedTime, const std::unordered_set<std::string>& choiceHistory) override;

    // Draw the box
    void draw(sf::RenderWindow& renderWindow, const std::unordered_set<std::string>& choiceHistory) override;

    // Update the image in the box
    void setImage(const sf::Texture* newImage);

    // Inherited methods
    // Set position of the box relative to the top left corner
    // virtual void setPosition(sf::Vector2f newPos);
  private:
    // The image to display
    std::unique_ptr<sf::Sprite> _image;

    // Inherited methods
    // The box rect
    //sf::IntRect _baseRect;
};


} // End namespace StoryTime


#endif // __ImageBox_H_INCLUDED__;
