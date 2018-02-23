#include "ChoiceBox.hpp"

namespace StoryTime {

// Constructor
ChoiceBox::ChoiceBox(sf::Font& font, std::vector<std::pair<std::string, std::string> >& choices, sf::Vector2f& pos, Markup& settings)
{
  // Create choice strings
  _choices.reserve(choices.size());
  _choiceNums.reserve(choices.size());
  for (int i = 0; i < choices.size(); i++)
  {
    std::pair<TextSegment, std::string> choice;
    choice.first = TextSegment(font, choices[i].first, 0.02, settings);
    choice.second = choices[i].second;
    _choices.push_back(choice);
    TextSegment choiceNum(font, std::to_string(i+1) + ".", 0.02, settings);
    _choiceNums.push_back(choiceNum);
  }
  // Set position of choices and box
  setPosition(pos);
}

void ChoiceBox::takeInput(sf::Event& curEvent)
{
  for (int i = 0; i < _choices.size(); i++)
  {
    if (curEvent.type == sf::Event::KeyPressed)
    {
      if (sf::Keyboard::isKeyPressed(Utils::getKeyByNumber(i+1)))
      {
        //std::cout << "Key pressed " << i+1 << std::endl;
        _choice = _choices[i];
        break;
      }
    }
  }
}

void ChoiceBox::update(sf::Time& elapsedTime)
{
  for (int i = 0; i < _choices.size(); i++)
  {
    _choices[i].first.update(elapsedTime);
    _choiceNums[i].update(elapsedTime);
  }
}

void ChoiceBox::draw(sf::RenderWindow& renderWindow)
{
  for (std::pair<TextSegment, std::string>& choice : _choices)
  {
    //std::cout << "here" << std::endl;
    //std::cout << (std::string)choice.getText().getString() << std::endl;
    //choice.printTargetText();
    renderWindow.draw(choice.first.getText());
    //choice.printTargetText();
  }
  for (TextSegment& number : _choiceNums)
  {
    //std::cout << "here" << std::endl;
    //std::cout << (std::string)choice.getText().getString() << std::endl;
    //choice.printTargetText();
    renderWindow.draw(number.getText());
    //choice.printTargetText();
  }
}

void ChoiceBox::setPosition(sf::Vector2f& newPos)
{
  _topLeft = newPos;
  _bottomRight = newPos;
  float tHeight = _choiceNums.front().getLocalBounds().height * 1.5;
  // Set the numbers
  for (TextSegment& number : _choiceNums)
  {
    // Set the choice's position
    number.getText().setPosition(newPos);
    // Update the height of the next choice
    newPos.y += tHeight;
  }
  // Set the text
  newPos.y -= tHeight * _choiceNums.size();
  // Add whitespace
  newPos.x += 2 * _choices.front().first.getText().getFont()->getGlyph('\u0009', _choices.front().first.getText().getCharacterSize(), false).advance;
  for (std::pair<TextSegment, std::string>& choice : _choices)
  {
    // Check if this is the widest string for the box so far
    sf::FloatRect bounds = choice.first.getLocalBounds();
    if (bounds.width > _bottomRight.x)
    {
      _bottomRight.x = bounds.width;
    }
    // Set the choice's position
    choice.first.getText().setPosition(newPos);
    // Update the height of the next choice
    newPos.y += tHeight;
  }
  // Update lower rightt corner y
  _bottomRight.y = newPos.y;
  // Add whitespace
  _bottomRight.x += 2 * _choices.front().first.getText().getFont()->getGlyph('\u0009', _choices.front().first.getText().getCharacterSize(), false).advance;
  
}

// If the choice is made this is either
// <continue> for a non-branching choice
// "" if no choice has been made
// And the id for the next story segment if a choice has been made
std::string& ChoiceBox::getChoiceId()
{
  return _choice.second;
}

std::unique_ptr<TextSegment> ChoiceBox::getChoiceText()
{
  if (_choice.second == "")
  {
    Markup markup{};
    return std::unique_ptr<TextSegment>(new TextSegment(GlobalSettings::DEFAULTFONT, "Choice not made!", -1.f, markup));
  } else {
    return std::unique_ptr<TextSegment>(new TextSegment(_choice.first));
  }
}

} // End namespace StoryTime