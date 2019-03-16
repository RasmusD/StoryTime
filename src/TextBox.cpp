#include "TextBox.hpp"

namespace StoryTime {

// Constructor
TextBox::TextBox(std::unique_ptr<TextSegment>& initialText,
                sf::IntRect boxRect)
              : Box(boxRect)
{
  _baseRect = boxRect;

  _screenText.push_back(std::move(initialText));
  _screenText.front()->getText().setPosition(static_cast<float>(_baseRect.left), static_cast<float>(_baseRect.top));
  redraw();
}

void TextBox::update(sf::Time& elapsedTime, std::unordered_set<std::string>& choiceHistory)
{
  //std::cout << "Updating text." << std::endl;
  // Update it
  _screenText.back()->update(elapsedTime, choiceHistory);
  // Check if the current segment is beyond the screen and a new line made
  sf::FloatRect bounds = _screenText.back()->getText().getGlobalBounds();
  //std::cout << GlobalSettings::WINDOWWIDTH << " bounds: " << bounds.left + bounds.width << std::endl;
  if (bounds.left + bounds.width >= static_cast<float>(_baseRect.width))
  {
    // If it is
    // Create a new segment. One line down
    _screenText.push_back(_screenText.back()->getRemainingTextSegment());
    _screenText.back()->getText().setPosition(static_cast<float>(_baseRect.left), _screenText.back()->getText().getPosition().y + static_cast<float>(GlobalSettings::getLineSpacing()));
    redraw();

    // Update bounds
    bounds = _screenText.back()->getText().getGlobalBounds();
  }
  // Check if lines should move up
  if (bounds.top + bounds.height >= (float)_baseRect.top + (float)_baseRect.height)
  {
    _moveTextLineUp();
  }

  if (_screenText.back()->needsDraw())
  {
    redraw();
  }
}

bool TextBox::atEnd()
{
  return _screenText.back()->atEnd;
}

void TextBox::draw(sf::RenderWindow& renderWindow, std::unordered_set<std::string>& choiceHistory)
{
  //std::cout << "Drwaing..." << std::endl;
  for (auto& segment : _screenText)
  {
    //std::cout << "Drwaing seg..." << std::endl;
    //segment->printTargetText();
    //segment->printVisibleText();
    segment->draw(renderWindow);
    //std::cout << "Done." << std::endl;
  }

  drawComplete();
}

// React to input
void TextBox::takeInput(sf::Event& curEvent, std::unordered_set<std::string>& choiceHistory)
{
  // Nothing
}

const sf::Color& TextBox::getBackgroundColour()
{
  return _screenText.back()->getBackgroundColour();
}

const std::string& TextBox::getDisplayImage()
{
  return _screenText.back()->getDisplayImage();
}

sf::Vector2f TextBox::bottomLeftCornerPos()
{
  return _screenText.back()->getText().getPosition();
}

void TextBox::_moveTextLineUp()
{
  // Move elements up by height
  sf::Vector2f pos;
  for (auto& seg : _screenText)
  {
    pos = seg->getText().getPosition();
    seg->getText().setPosition(pos.x, pos.y - static_cast<float>(GlobalSettings::getLineSpacing()));
  }
  // Get rid of all the obsolete elements
  sf::FloatRect bounds = _screenText.front()->getText().getGlobalBounds();
  while (bounds.top + bounds.height <= static_cast<float>(_baseRect.top))
  {
    _screenText.pop_front();
    bounds = _screenText.front()->getText().getGlobalBounds();
  }
  redraw();
}

void TextBox::addTextSegment(std::unique_ptr<TextSegment>& segment)
{
  // Set position of next segment
  sf::Vector2f sPos = _screenText.back()->getText().getPosition();;
  if (((std::string)_screenText.back()->getText().getString()).back() == '\n')
  {
    sPos.x = static_cast<float>(_baseRect.left);
    sPos.y += static_cast<float>(GlobalSettings::getLineSpacing());
  } else {
    sPos.x += _screenText.back()->getText().getLocalBounds().width;
  }
  _screenText.push_back(std::move(segment));
  _screenText.back()->getText().setPosition(sPos);
  redraw();
}

} // End namespace StoryTime
