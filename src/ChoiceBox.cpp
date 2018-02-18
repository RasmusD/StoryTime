#include "ChoiceBox.hpp"

namespace StoryTime {

// Constructor
ChoiceBox::ChoiceBox(sf::Font& font, std::vector<std::pair<std::string, int> >& choices, sf::Vector2f& pos)
{
  // Create choice strings
  _choices.reserve(choices.size());
  _choiceNums.reserve(choices.size());
  for (int i = 0; i < choices.size(); i++)
  {
    TextSegment choice(font, choices[i].first, 0.02);
    _choices.push_back(choice);
    TextSegment choiceNum(font, std::to_string(i+1) + ".", 0.02);
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
        std::cout << "Key pressed " << i+1 << std::endl;
        _choice = i+1;
        break;
      }
    }
  }
}

void ChoiceBox::update(sf::Time& elapsedTime)
{
  for (int i = 0; i < _choices.size(); i++)
  {
    _choices[i].update(elapsedTime);
    _choiceNums[i].update(elapsedTime);
  }
}

void ChoiceBox::draw(sf::RenderWindow& renderWindow)
{
  for (TextSegment& choice : _choices)
  {
    //std::cout << "here" << std::endl;
    //std::cout << (std::string)choice.getText().getString() << std::endl;
    //choice.printTargetText();
    renderWindow.draw(choice.getText());
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
  newPos.x += 2 * _choices.front().getText().getFont()->getGlyph('\u0009', _choices.front().getText().getCharacterSize(), false).advance;
  for (TextSegment& choice : _choices)
  {
    // Check if this is the widest string for the box so far
    sf::FloatRect bounds = choice.getLocalBounds();
    if (bounds.width > _bottomRight.x)
    {
      _bottomRight.x = bounds.width;
    }
    // Set the choice's position
    choice.getText().setPosition(newPos);
    // Update the height of the next choice
    newPos.y += tHeight;
  }
  // Update lower rightt corner y
  _bottomRight.y = newPos.y;
  // Add whitespace
  _bottomRight.x += 2 * _choices.front().getText().getFont()->getGlyph('\u0009', _choices.front().getText().getCharacterSize(), false).advance;
  
}

int ChoiceBox::getChoice()
{
  return _choice;
}

std::unique_ptr<TextSegment> ChoiceBox::getChoiceText()
{
  if (_choice < 0)
  {
    return std::unique_ptr<TextSegment>(new TextSegment(GlobalSettings::DEFAULTFONT, "Choice not made!", -1.f));
  } else {
    return std::unique_ptr<TextSegment>(new TextSegment(_choices[_choice-1]));
  }
}

} // End namespace StoryTime