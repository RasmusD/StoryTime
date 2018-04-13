// The main game

// Include guard
#ifndef __TextHandler_H_INCLUDED__
#define __TextHandler_H_INCLUDED__

#include <iostream>
#include <deque>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include <SFML/Graphics.hpp>

#include "GlobalSettings.hpp"
#include "Utils.hpp"
#include "TextSegment.hpp"
#include "TextParser.hpp"
#include "ChoiceBox.hpp"

namespace StoryTime {

class TextHandler
{
  public:
    // Constructor
    TextHandler(std::unordered_map<std::string, std::string>& storyData, Markup& defaultMarkup);

    // Destuctor
    ~TextHandler() {};

    // React to input
    void takeInput(sf::Event& curEvent);

    // Update the text handler
    void update(sf::Time& elapsedTime);

    // Draw
    void draw(sf::RenderWindow& renderWindow);

    // Get the background colour of the current segment
    sf::Color& getBackgroundColour();

  private:
    // Methods
    void setNextSegment();
    void setTextNext();
    void setChoiceNext();

    // Add a new branch
    void addBranch(std::string& id);

    // Move screen text one line up
    void moveTextLineUp();

    // Variables

    // Dictionary of branching story segments
    std::unordered_map<std::string, std::string> _storyData;
    // Ordered list of TextSegments and ChoiceBoxes to go through
    std::deque<Utils::SegChoice> _segmentQueue;
    // The text to currently be displayed
    std::deque<std::unique_ptr<TextSegment>> _screenText;
    // Current choice
    std::unique_ptr<ChoiceBox> _currentChoice;
    // List of previously made choices
    std::unordered_set<std::string> _choiceHistory;
    // Are we currently making a choice?
    bool _choiceActive;
    // Should the next segment be a choice or text?
    bool _isNextChoice;
    // The default markup for text parsing
    Markup _defaultMarkup;
};


} // End namespace StoryTime


#endif // __TextHandler_H_INCLUDED__;