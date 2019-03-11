// The main game

// Include guard
#ifndef __TextSegment_H_INCLUDED__
#define __TextSegment_H_INCLUDED__

#include <iostream>
#include <memory>
#include <unordered_set>

#include <SFML/Graphics.hpp>

#include "GlobalSettings.hpp"

namespace StoryTime {

class TextSegment
{
  public:
    // Constructor
    TextSegment(const sf::Font& font, std::string text, Markup& settings);
    TextSegment(const sf::Font& font, std::string text, Markup& settings, std::vector<std::pair<std::string, std::string> >& alternatives);
    TextSegment();

    // Destuctor
    ~TextSegment() {};

    // Update the text
    void update(sf::Time& elapsedTime, std::unordered_set<std::string>& choiceHistory);

    // See if the text segment requires a draw
    bool needsDraw();

    // Indicate that the draw has been completed
    void drawComplete();

    // Draw the text
    void draw(sf::RenderWindow& renderWindow);

    // Get the background colour for this segment
    // Note this is the background for the full screen
    sf::Color& getBackgroundColour();

    // Returns the local bounds of the text once the full target text has been rendered
    sf::FloatRect getLocalBounds();

    // A bool which tells whether the segment is fully rendered
    bool atEnd;

    // Print the target text. For debug.
    void printTargetText();

    // Print the visible text. For debug.
    void printVisibleText();

    // Access to the currently visible text
    sf::Text& getText();

    // Add more text to the final target text
    void addText(std::string& toAdd);

    // Get the remaining text not currently shown
    std::unique_ptr<TextSegment> getRemainingTextSegment();

    // Reset the visible text
    void resetText();

    Markup getSettings();

  private:
    // The currently visible text
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
    // Saving the settings
    Markup _settings;
    // Alternative text to display, depending on previous choices
    std::vector<std::pair<std::string, std::string> > _alternatives;
    // Shows if this segment has ever had update called on it (sets variables)
    bool _updated = false;
    // Shows whether a draw has been requested
    bool _needsDraw = false;

    // Methods
    // Change the text - e.g. if alternative should be used
    void _changeText(std::string& text);
};

} // End namespace StoryTime


#endif // __TextSegment_H_INCLUDED__;
