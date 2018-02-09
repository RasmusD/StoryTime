// The main game

// Include guard
#ifndef __ChoiceBox_H_INCLUDED__
#define __ChoiceBox_H_INCLUDED__

#include <iostream>

#include <SFML/Graphics.hpp>

#include "GlobalSettings.hpp"
#include "TextSegment.hpp"

namespace StoryTime {

class ChoiceBox
{
  public:
    // Constructor
    ChoiceBox(sf::Font& font, std::vector<std::pair<std::string, int>>& choices, sf::Vector2f& pos);
    ChoiceBox() {};

    // Destuctor
    ~ChoiceBox() {};

    // Update the box
    void update(sf::Time& elapsedTime);

    // Draw the box
    void draw(sf::RenderWindow& renderWindow);

    // Set position of the box relative to the top left corner
    void setPosition(sf::Vector2f& newPos);
  private:
    // The choices which can be made
    std::vector<TextSegment> _choices;

    // The top left corner position
    sf::Vector2f _topLeft;

    // The bottom right corner position
    sf::Vector2f _bottomRight;
};


} // End namespace StoryTime


#endif // __ChoiceBox_H_INCLUDED__;