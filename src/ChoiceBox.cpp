#include "ChoiceBox.hpp"

namespace StoryTime {

// Constructor
ChoiceBox::ChoiceBox(std::vector<Choice>& choices,
                    sf::Vector2f& pos,
                    Markup& settings,
                    ChoiceType type)
{
  // If there are no choices - throw
  // TMP - should not throw
  if (choices.size() == 0)
  {
    throw std::runtime_error("ChoiceBox: No choices for choicebox!");
  }
  // Create choice strings
  _choices.reserve(choices.size());
  _choiceNums.reserve(choices.size());
  for (int i = 0; i < choices.size(); i++)
  {
    _choices.push_back(choices[i]);
    TextSegment choiceNum(*choices[i].text.getText().getFont(), std::to_string(i+1) + ".", settings);
    _choiceNums.push_back(choiceNum);
  }
  // Set choice type
  _type = type;
  // Set position of choices and box
  setPosition(pos);
  // If there is only one choice - mark it as already chosen
  if (choices.size() == 1)
  {
    _choice = _choices[0];
  }
}

void ChoiceBox::takeInput(sf::Event& curEvent, std::unordered_set<std::string>& choiceHistory)
{
  // If no choice has been made - check if one is made now
  if (_choice.id == "")
  {
    for (int i = 0; i < _choices.size(); i++)
    {
      if (_choices[i].prereq != "")
      {
        if (choiceHistory.count(_choices[i].prereq) == 0)
        {
          // Skip
          continue;
        }
      }
      if (curEvent.type == sf::Event::KeyPressed)
      {
        if (sf::Keyboard::isKeyPressed(Utils::getKeyByNumber(i+1)))
        {
          //std::cout << "Key pressed " << i+1 << std::endl;
          _choice = _choices[i];
          choiceHistory.insert(_choice.id);
          break;
        }
      }
    }
  }
}

void ChoiceBox::update(sf::Time& elapsedTime, std::unordered_set<std::string>& choiceHistory)
{
  for (int i = 0; i < _choices.size(); i++)
  {
    if (_choices[i].prereq != "")
    {
      if (choiceHistory.count(_choices[i].prereq) == 0)
      {
        // Skip
        continue;
      }
    }
    _choices[i].text.update(elapsedTime, choiceHistory);
    _choiceNums[i].update(elapsedTime, choiceHistory);
  }
}

void ChoiceBox::draw(sf::RenderWindow& renderWindow, std::unordered_set<std::string>& choiceHistory)
{
  for (Choice& choice : _choices)
  {
    if (choice.prereq != "")
    {
      if (choiceHistory.count(choice.prereq) == 0)
      {
        // Skip
        continue;
      }
    }
    //std::cout << "here" << std::endl;
    //std::cout << (std::string)choice.getText().getString() << std::endl;
    //choice.printTargetText();
    renderWindow.draw(choice.text.getText());
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
  newPos.x += 2 * _choices.front().text.getText().getFont()->getGlyph('\u0009', _choices.front().text.getText().getCharacterSize(), false).advance;
  for (Choice& choice : _choices)
  {
    // Check if this is the widest string for the box so far
    sf::FloatRect bounds = choice.text.getLocalBounds();
    if (bounds.width > _bottomRight.x)
    {
      _bottomRight.x = bounds.width;
    }
    // Set the choice's position
    choice.text.getText().setPosition(newPos);
    // Update the height of the next choice
    newPos.y += tHeight;
  }
  // Update lower rightt corner y
  _bottomRight.y = newPos.y;
  // Add whitespace
  _bottomRight.x += 2 * _choices.front().text.getText().getFont()->getGlyph('\u0009', _choices.front().text.getText().getCharacterSize(), false).advance;
  
}

// If the choice is made this is either
// <continue> for a non-branching choice
// "" if no choice has been made
// And the id for the next story segment if a choice has been made
std::string ChoiceBox::getChoiceId()
{
  if (_choice.id != "" and _type == ChoiceType::VALUE)
  {
    return "<continue>";
  } else {
    return _choice.id;
  }
}

std::vector<Choice> ChoiceBox::getChoices()
{
  return _choices;
}

int ChoiceBox::getNumChoices()
{
  return _choices.size();
}

std::unique_ptr<TextSegment> ChoiceBox::getChoiceText()
{
  if (_choice.id == "")
  {
    Markup settings = GlobalSettings::currentSettings;
    settings.speed = -1.f;
    return std::unique_ptr<TextSegment>(new TextSegment(GlobalSettings::DEFAULTFONT, "Choice not made!", GlobalSettings::currentSettings));
  } else {
    return std::unique_ptr<TextSegment>(new TextSegment(_choice.text));
  }
}

ChoiceType ChoiceBox::getChoiceType()
{
  return _type;
}

} // End namespace StoryTime