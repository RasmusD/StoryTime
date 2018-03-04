// The main game

// Include guard
#ifndef __ChoiceBox_H_INCLUDED__
#define __ChoiceBox_H_INCLUDED__

#include <iostream>
#include <unordered_set>

#include <SFML/Graphics.hpp>

#include "Utils.hpp"
#include "GlobalSettings.hpp"
#include "TextSegment.hpp"

namespace StoryTime {

// Enum for types of choices
enum class ChoiceType
{
    BRANCH,
    VALUE
};

class ChoiceBox
{
  public:
    // Constructor
    ChoiceBox(sf::Font& font, std::vector<std::pair<std::string, std::string>>& choices, sf::Vector2f& pos, Markup& settings, ChoiceType type);
    ChoiceBox() {};

    // Destuctor
    ~ChoiceBox() {};

    // React to input
    void takeInput(sf::Event& curEvent, std::unordered_set<std::string>& choiceHistory);

    // Update the box
    void update(sf::Time& elapsedTime);

    // Draw the box
    void draw(sf::RenderWindow& renderWindow);

    // Set position of the box relative to the top left corner
    void setPosition(sf::Vector2f& newPos);

    // Returns the identifier of the next text segment if a choice has been made
    // Returns "<continue>" if not a branching choice
    // Returns "" if no choice has been made
    std::string getChoiceId();

    // Returns the chosen textsegment
    std::unique_ptr<TextSegment> getChoiceText();

    // Get the choice type of this choice
    ChoiceType getChoiceType();

  private:
    // The choices which can be made
    std::vector<std::pair<TextSegment, std::string>> _choices;

    // The type of choice
    ChoiceType _type;

    // The choices numbers
    std::vector<TextSegment> _choiceNums;

    // The top left corner position
    sf::Vector2f _topLeft;

    // The bottom right corner position
    sf::Vector2f _bottomRight;

    // The choice made
    // "" while no choice has been made
    std::pair<TextSegment, std::string> _choice = {TextSegment(), ""};
};


} // End namespace StoryTime


#endif // __ChoiceBox_H_INCLUDED__;