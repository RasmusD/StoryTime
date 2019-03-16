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

class TextBox : public Box
{
  public:
    // Constructor
    TextBox(std::unique_ptr<TextSegment>& initialText,
            sf::IntRect boxRect);

    // Destuctor
    ~TextBox() {};

    // Update the text handler
    void update(sf::Time& elapsedTime, std::unordered_set<std::string>& choiceHistory) override;

    // Draw the box
    void draw(sf::RenderWindow& renderWindow, std::unordered_set<std::string>& choiceHistory) override;
    
    // React to input
    void takeInput(sf::Event& curEvent, std::unordered_set<std::string>& choiceHistory) override;

    // Check if the text box is at the end of the current screen text to update
    bool atEnd();

    // Add a segment of text to the text box
    void addTextSegment(std::unique_ptr<TextSegment>& segment);

    // Get the background colour of the current segment
    const sf::Color& getBackgroundColour();

    // Get the image to be displayed with the current text segment
    const std::string& getDisplayImage();

    // Get the lower left corner of the box
    sf::Vector2f bottomLeftCornerPos();

    // Inherited from base and not overriden
    // void setPosition(sf::Vector2f newPos);

  private:
    // Move screen text one line up
    void _moveTextLineUp();

    // Variables
    // The text to currently be displayed
    std::deque<std::unique_ptr<TextSegment>> _screenText;
    // The default markup for text parsing
    Markup _defaultMarkup;

    // Inherited from base
    // Box rectangle
    //sf::IntRect _baseRect;
};


} // End namespace StoryTime


#endif // __TextBox_H_INCLUDED__;
