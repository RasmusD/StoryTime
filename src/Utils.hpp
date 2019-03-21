// Utility functions

// Include guard
#ifndef __Utils_H_INCLUDED__
#define __Utils_H_INCLUDED__

#include <iostream>
#include <unordered_set>

#include <SFML/Graphics.hpp>

#include "TextSegment.hpp"
#include "ChoiceBox.hpp"

namespace StoryTime {

class ChoiceBox;

class Utils
{
  public:
    template <typename TO, typename FROM>
    static sf::Vector2<TO> toVector2(const sf::Vector2<FROM> &other)
    {
        return sf::Vector2<TO>(
            static_cast<TO>(other.x),
            static_cast<TO>(other.y));
    }

    // A structure with a pointer to a text or choice
    struct SegChoice
    {
      SegChoice(){};
      // Move constructor
      SegChoice(SegChoice&& move)
      {
        text = std::move(move.text);
        choice = std::move(move.choice);
      };
      ~SegChoice(){};
      bool operator==(const SegChoice& other) 
      {
        return (text == other.text && choice == other.choice);
      };
      std::unique_ptr<TextSegment> text;
      std::unique_ptr<ChoiceBox> choice;
      std::string newId = "";
    };

    // Gets an sf::Keyboard::Key enum by number 0 - 9
    static sf::Keyboard::Key getKeyByNumber(int num)
    {
      switch (num)
      {
        case 0:
          return sf::Keyboard::Key::Num0;
        case 1:
          return sf::Keyboard::Key::Num1;
        case 2:
          return sf::Keyboard::Key::Num2;
        case 3:
          return sf::Keyboard::Key::Num3;
        case 4:
          return sf::Keyboard::Key::Num4;
        case 5:
          return sf::Keyboard::Key::Num5;
        case 6:
          return sf::Keyboard::Key::Num6;
        case 7:
          return sf::Keyboard::Key::Num7;
        case 8:
          return sf::Keyboard::Key::Num8;
        case 9:
          return sf::Keyboard::Key::Num9;
        default:
          return sf::Keyboard::Key::Unknown;
      }
    }

    // Split a string on a string delimiter to a set of strings
    static void splitStringToSet(std::string stringToSplit,
                                std::unordered_set<std::string>& outSet,
                                std::string delimiter)
    {
      size_t cpos = 0;
      size_t ppos = 0;
      while ((ppos = stringToSplit.find(delimiter, cpos)) != std::string::npos)
      {
        outSet.insert(stringToSplit.substr(cpos, ppos - cpos));
        cpos = ppos + delimiter.length();
      }

      outSet.insert(stringToSplit.substr(cpos));
    }
};


} // End namespace StoryTime


#endif // __Utils_H_INCLUDED__;