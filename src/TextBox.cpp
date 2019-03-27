#include "TextBox.hpp"

namespace StoryTime {

// Constructor
TextBox::TextBox(std::unique_ptr<TextSegment>& initialText,
                sf::IntRect boxRect)
              : Box(boxRect)
{
  _baseRect = boxRect;

  _screenText.push_back(std::move(initialText));
  _screenText.front()->getVisibleText().setPosition(static_cast<float>(_baseRect.left), static_cast<float>(_baseRect.top));
  redraw();
}

void TextBox::update(sf::Time& elapsedTime, const std::unordered_set<std::string>& choiceHistory)
{
  //std::cout << "Updating text." << std::endl;
  // Update it
  _screenText.back()->update(elapsedTime, choiceHistory);
  // Check if the current segment is beyond the screen and a new line made
  sf::FloatRect bounds = _screenText.back()->getVisibleText().getGlobalBounds();
  //std::cout << GlobalSettings::WINDOWWIDTH << " bounds: " << bounds.left + bounds.width << std::endl;
  //std::cout << "_baseRect: " << _baseRect.left + _baseRect.width << std::endl;
  if (bounds.left + bounds.width >= static_cast<float>(_baseRect.left + _baseRect.width))
  {
    // If it is
    // Create a new segment. One line down
    _screenText.push_back(_screenText.back()->getRemainingTextSegment(_baseRect.left + _baseRect.width));
    _screenText.back()->getVisibleText().setPosition(static_cast<float>(_baseRect.left), _screenText.back()->getVisibleText().getPosition().y + static_cast<float>(GlobalSettings::getLineSpacing()));
    redraw();

    // Update bounds
    bounds = _screenText.back()->getVisibleText().getGlobalBounds();
  }

  // Check if lines should move up
  //std::cout << "b " << bounds.top + static_cast<float>(GlobalSettings::getCharSize()) << std::endl;
  //std::cout << "r " << static_cast<float>(_baseRect.top + _baseRect.height) << std::endl;
  if (bounds.top + static_cast<float>(GlobalSettings::getCharSize()) > static_cast<float>(_baseRect.top + _baseRect.height))
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

void TextBox::draw(sf::RenderWindow& renderWindow, const std::unordered_set<std::string>& choiceHistory)
{
  //std::cout << "Drwaing..." << std::endl;
  for (auto& segment : _screenText)
  {
    //std::cout << "Drwaing seg..." << std::endl;
    //segment->printTargetText();
    //segment->printVisibleText();
    //std::cout << segment->getVisibleText().getPosition().x << " " << segment->getVisibleText().getPosition().y << std::endl;
    //std::cout << _baseRect.top << std::endl;
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
  return _screenText.back()->getVisibleText().getPosition();
}

void TextBox::_moveTextLineUp()
{
  // Move elements up by height
  sf::Vector2f pos;
  for (auto& seg : _screenText)
  {
    pos = seg->getVisibleText().getPosition();
    seg->getVisibleText().setPosition(pos.x, pos.y - static_cast<float>(GlobalSettings::getLineSpacing()));
  }

  // Get rid of all the obsolete elements
  sf::FloatRect bounds = _screenText.front()->getVisibleText().getGlobalBounds();
  while (bounds.top <= static_cast<float>(_baseRect.top))
  {
    _screenText.pop_front();
    bounds = _screenText.front()->getVisibleText().getGlobalBounds();
  }
  redraw();
}

void TextBox::addTextSegment(std::unique_ptr<TextSegment>& segment, const std::unordered_set<std::string>& choiceHistory)
{
  // First make sure segment has been checked for variants depending on history
  segment->updateBasics(choiceHistory);
  // Simply ignore empty segments
  if (segment->getTargetText() == "")
  {
    return;
  }
  // Set position of next segment
  sf::Vector2f sPos = _screenText.back()->getVisibleText().getPosition();
  const std::string& backStr = _screenText.back()->getTargetText();
  if (backStr.back() == '\n' and backStr != "\n")
  {
    sPos.x = static_cast<float>(_baseRect.left);
    sPos.y += static_cast<float>(GlobalSettings::getLineSpacing());
  } else if (backStr == "\n") {
    // Find out if we have three newline in a row. If so we ignore this newline
    size_t size = _screenText.size();
    if (size > 2 and
        _screenText[size - 2]->getTargetText() == "\n" and
        _screenText[size - 3]->getTargetText().back() == '\n')
    {
      // Ignore
    } else {
      sPos.x = static_cast<float>(_baseRect.left);
      sPos.y += static_cast<float>(GlobalSettings::getLineSpacing());
    }
  } else {
    sPos.x += _screenText.back()->getVisibleText().getLocalBounds().width;
  }
  _screenText.push_back(std::move(segment));
  _screenText.back()->getVisibleText().setPosition(sPos);
  redraw();
}

} // End namespace StoryTime
