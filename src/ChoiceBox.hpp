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
#include "Box.hpp"

namespace StoryTime {

// Enum for types of choices
enum class ChoiceType
{
  BRANCH,
  VALUE
};

struct Choice
{
  TextSegment text;
  std::string id = "";
  std::string prereq = "";
};

class ChoiceBox : public Box
{
  public:
    // Constructor
    ChoiceBox(std::vector<Choice>& choices,
              sf::IntRect boxRect,
              Markup& settings,
              ChoiceType type);

    // Destuctor
    ~ChoiceBox() {};

    // React to input
    void takeInput(sf::Event& curEvent, std::unordered_set<std::string>& choiceHistory) override;

    // Update the box
    void update(sf::Time& elapsedTime, std::unordered_set<std::string>& choiceHistory) override;

    // Draw the box
    void draw(sf::RenderWindow& renderWindow, std::unordered_set<std::string>& choiceHistory) override;

    // Get the background color of the choice
    const sf::Color& getBackgroundColour();

    // Get the display image of the choice
    const std::string& getDisplayImage();

    // Set position of the box relative to the top left corner
    void setPosition(sf::Vector2f newPos) override;

    // Set the choice box rectangle
    void setBoxRect(sf::IntRect newRect) override;

    // Returns the identifier of the next text segment if a choice has been made
    // Returns "<continue>" if not a branching choice
    // Returns "" if no choice has been made
    std::string getChoiceId();

    // Returns the possible choices
    std::vector<Choice> getChoices();

    // Returns the number of possible choices
    int getNumChoices();

    // Returns the chosen textsegment
    std::unique_ptr<TextSegment> getChoiceText();

    // Get the choice type of this choice
    ChoiceType getChoiceType();

    // Get the settings
    Markup getSettings();

  private:
    // The choices which can be made
    std::vector<Choice> _choices;

    // The type of choice
    ChoiceType _type;

    // The choices numbers
    std::vector<TextSegment> _choiceNums;

    // The choice made
    // Default while no choice has been made
    Choice _choice;

    Markup _settings;

    // Inherited from base class
    // The top left corner position
    //sf::IntRect _baseRect;
};


} // End namespace StoryTime


#endif // __ChoiceBox_H_INCLUDED__;
