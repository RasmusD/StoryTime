// The main game

// Include guard
#ifndef __TextHandler_H_INCLUDED__
#define __TextHandler_H_INCLUDED__

#include <iostream>
#include <deque>

#include <SFML/Graphics.hpp>

#include "GlobalSettings.hpp"
#include "TextSegment.hpp"
#include "TextParser.hpp"
#include "ChoiceBox.hpp"

namespace StoryTime {

class TextHandler
{
  public:
    // Constructor
    TextHandler(std::string& inTxt);

    // Destuctor
    ~TextHandler() {};

    // Update the text handler
    void update(sf::Event& curEvent, sf::Event& prevEvent, sf::Time& elapsedTime);

    // Draw
    void draw(sf::RenderWindow& renderWindow);

  private:
    // Methods
    void setNextSegment();

    // Variables
    // List of all text segments, in order to play
    std::deque<TextSegment> _segments;
    // List of all choices to make, in order to make
    std::deque<ChoiceBox> _choices;
    // The core text to be displayed
    TextSegment _coreText;
    // Current choice
    ChoiceBox _currentChoice;
    // Are we currently making a choice?
    bool _choiceActive;
};


} // End namespace StoryTime


#endif // __TextHandler_H_INCLUDED__;