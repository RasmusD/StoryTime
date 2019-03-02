#include "TextBox.hpp"

namespace StoryTime {

// Constructor
TextBox::TextBox(std::unique_ptr<TextSegment>& initialText,
                Markup& defaultMarkup,
                sf::IntRect boxRect)
              : Box(boxRect)
{
  _defaultMarkup = defaultMarkup;

  _baseRect = boxRect;

  _screenText.push_back(std::move(initialText));
  _screenText.front()->getText().setPosition(_baseRect.left, _baseRect.top);
}

void TextBox::update(sf::Time& elapsedTime, std::unordered_set<std::string>& choiceHistory)
{
  //std::cout << "Updating text." << std::endl;
  // Update it
  _screenText.back()->update(elapsedTime, choiceHistory);
  // Check if the current segment is beyond the screen and a new line made
  sf::FloatRect bounds = _screenText.back()->getText().getGlobalBounds();
  //std::cout << GlobalSettings::WINDOWWIDTH << " bounds: " << bounds.left + bounds.width << std::endl;
  if (bounds.left + bounds.width >= _baseRect.width)
  {
    // If it is
    // Create a new segment. One line down
    _screenText.push_back(_screenText.back()->getRemainingTextSegment());
    _screenText.back()->getText().setPosition(_baseRect.left, _screenText.back()->getText().getPosition().y + GlobalSettings::getLineSpacing());
    // Update bounds
    bounds = _screenText.back()->getText().getGlobalBounds();
  }
  // Check if lines should move up
  if (bounds.top + bounds.height >= GlobalSettings::WINDOWHEIGHT)
  {
    moveTextLineUp(bounds);
  }
}

bool TextBox::atEnd()
{
  return _screenText.back()->atEnd;
}

void TextBox::draw(sf::RenderWindow& renderWindow)
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
}

sf::Color& TextBox::getBackgroundColour()
{
  return _screenText.back()->getBackgroundColour();
}

sf::Vector2f TextBox::bottomLeftCornerPos()
{
  return _screenText.back()->getText().getPosition();
}

void TextBox::moveTextLineUp(sf::FloatRect& bounds)
{
  // Move elements up by height
  sf::Vector2f pos;
  for (auto& seg : _screenText)
  {
    pos = seg->getText().getPosition();
    seg->getText().setPosition(pos.x, pos.y - GlobalSettings::getLineSpacing());
  }
  // Get rid of all the obsolete elements
  // We assume height is valid
  while (_screenText.front()->getText().getGlobalBounds().top + bounds.height <= 0)
  {
    _screenText.pop_front();
  }
}

void TextBox::addTextSegment(std::unique_ptr<TextSegment>& segment)
{
  // Set position of next segment
  sf::Vector2f sPos = _screenText.back()->getText().getPosition();;
  if (((std::string)_screenText.back()->getText().getString()).back() == '\n')
  {
    sPos.x = _baseRect.left;
    sPos.y += GlobalSettings::getLineSpacing();
  } else {
    sPos.x += _screenText.back()->getText().getLocalBounds().width;
  }
  _screenText.push_back(std::move(segment));
  _screenText.back()->getText().setPosition(sPos);
}

} // End namespace StoryTime