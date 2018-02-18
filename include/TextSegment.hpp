// The main game

// Include guard
#ifndef __TextSegment_H_INCLUDED__
#define __TextSegment_H_INCLUDED__

#include <iostream>

#include <SFML/Graphics.hpp>

#include "GlobalSettings.hpp"

namespace StoryTime {

class TextSegment
{
  public:
    // Constructor
    TextSegment(const sf::Font& font, std::string text, float drawSpeed);
    TextSegment();

    // Destuctor
    ~TextSegment() {};

    // Update the text
    void update(sf::Time& elapsedTime);

    // Draw the text
    void draw(sf::RenderWindow& renderWindow);

    // Returns the local bounds of the text once the full target text has been rendered
    sf::FloatRect getLocalBounds();

    // A bool which tells whether the segment is fully rendered
    bool atEnd;

    // Print the target text. For debug.
    void printTargetText();

    // Print the visible text. For debug.
    void printVisibleText();

    // Access to the currently visible text
    sf::Text* getText();

    // Add more text to the final target text
    void addText(std::string& toAdd);

    // Get the remaining text not currently shown
    std::unique_ptr<TextSegment> getRemainingTextSegment();

  private:
    // Private hidden constructor
    sf::Text _text;
    // The text segment once fully realised
    std::string _targetText;
    // The current position in the final text
    unsigned int _stringPos = 0;
    // The speed in s with which the text renders
    // If set to -1.f it will render fully from the start.
    float _drawSpeed = -1.f;
    // A counter to keep track of drawing speed
    float _timeCount = 0.f;
};


} // End namespace StoryTime


#endif // __TextSegment_H_INCLUDED__;