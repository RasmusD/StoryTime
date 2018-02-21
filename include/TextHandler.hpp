// The main game

// Include guard
#ifndef __TextHandler_H_INCLUDED__
#define __TextHandler_H_INCLUDED__

#include <iostream>
#include <deque>
#include <memory>

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
    TextHandler(std::unordered_map<std::string, std::string>& storyData);

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

    // Add a new branch
    void addBranch(std::string& id);

    // Variables
    // Dictionary of branching story segments
    std::unordered_map<std::string, std::string> _storyData;
    // Ordered list of TextSegments and ChoiceBoxes to go through
    std::deque<Utils::SegChoice> _segmentQueue;
    // The text to currently be displayed
    std::vector<std::unique_ptr<TextSegment>> _screenText;
    // Current choice
    std::unique_ptr<ChoiceBox> _currentChoice;
    // Are we currently making a choice?
    bool _choiceActive;
    // Should the next segment be a choice or text?
    bool _isNextChoice;
};


} // End namespace StoryTime


#endif // __TextHandler_H_INCLUDED__;