// The main game

// Include guard
#ifndef __TextBox_H_INCLUDED__
#define __TextBox_H_INCLUDED__

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
#include "GameSaver.hpp"

namespace StoryTime {

class TextBox
{
  public:
    // Constructor
    TextBox(std::unique_ptr<TextSegment>& initialText, Markup& defaultMarkup, size_t x, size_t y);

    // Destuctor
    ~TextBox() {};

    // Update the text handler
    void update(sf::Time& elapsedTime, std::unordered_set<std::string>& choiceHistory);

    // Draw
    void draw(sf::RenderWindow& renderWindow);

    // Check if the text box is at the end of the current screen text to update
    bool atEnd();

    // Add a segment of text to the text box
    void addTextSegment(std::unique_ptr<TextSegment>& segment);

    // Get the background colour of the current segment
    sf::Color& getBackgroundColour();

    // Get the lower left corner of the box
    sf::Vector2f bottomLeftCornerPos();

  private:
    // Move screen text one line up
    void moveTextLineUp(sf::FloatRect& bounds);

    // Variables
    // X/Y base position
    size_t _baseX;
    size_t _baseY;
    // The text to currently be displayed
    std::deque<std::unique_ptr<TextSegment>> _screenText;
    // The default markup for text parsing
    Markup _defaultMarkup;
};


} // End namespace StoryTime


#endif // __TextBox_H_INCLUDED__;