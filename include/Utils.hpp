// Utility functions

// Include guard
#ifndef __Utils_H_INCLUDED__
#define __Utils_H_INCLUDED__

#include <iostream>

#include <SFML/Graphics.hpp>

namespace StoryTime {

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
};


} // End namespace StoryTime


#endif // __Utils_H_INCLUDED__;