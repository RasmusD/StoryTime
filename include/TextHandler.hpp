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

    // React to input
    void takeInput(sf::Event& curEvent);

    // Update the text handler
    void update(sf::Time& elapsedTime);

    // Draw
    void draw(sf::RenderWindow& renderWindow);

  private:
    // Methods
    void setNextSegment();
    void setTextNext();
    void setChoiceNext();

    // Variables
    // List of all text segments, in order to play
    std::deque<TextSegment> _segments;
    // List of all choices to make, in order to make
    std::deque<ChoiceBox> _choices;
    // The core text to be displayed
    std::vector<TextSegment> _screenText;
    // Current choice
    ChoiceBox _currentChoice;
    // Are we currently making a choice?
    bool _choiceActive;
    // Should the next segment be a choice or text?
    bool _isNextChoice;
};


} // End namespace StoryTime


#endif // __TextHandler_H_INCLUDED__;