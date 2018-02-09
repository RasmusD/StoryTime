#include "ChoiceBox.hpp"

namespace StoryTime {

// Constructor
ChoiceBox::ChoiceBox(sf::Font& font, std::vector<std::pair<std::string, int> >& choices, sf::Vector2f& pos)
{
  // Create choice strings
  _choices.reserve(choices.size());
  for (int i = 0; i < choices.size(); i++)
  {
    TextSegment choice(font, std::to_string(i+1) + ". " + choices[i].first, 0.02);
    _choices.push_back(choice);
  }
  // Set position of choices and box
  setPosition(pos);
}

void ChoiceBox::update(sf::Time& elapsedTime)
{
  for (TextSegment& choice : _choices)
  {
    choice.update(elapsedTime);
  }
}

void ChoiceBox::draw(sf::RenderWindow& renderWindow)
{
  for (TextSegment& choice : _choices)
  {
    //std::cout << "here" << std::endl;
    //std::cout << (std::string)choice.getText()->getString() << std::endl;
    //choice.printTargetText();
    renderWindow.draw(*choice.getText());
    //choice.printTargetText();
  }
}

void ChoiceBox::setPosition(sf::Vector2f& newPos)
{
  _topLeft = newPos;
  _bottomRight = newPos;
  for (TextSegment& choice : _choices)
  {
    // Check if this is the widest string for the box so far
    sf::FloatRect bounds = choice.getLocalBounds();
    if (bounds.width > _bottomRight.x)
    {
      _bottomRight.x = bounds.width;
    }
    // Set the choice's position
    choice.getText()->setPosition(newPos);
    // Update the height of the next choice
    newPos.y += bounds.height + 10;
  }
  // Update lower rightt corner y
  _bottomRight.y = newPos.y - 10;
}

} // End namespace StoryTime