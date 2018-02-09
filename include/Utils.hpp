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
};


} // End namespace StoryTime


#endif // __Utils_H_INCLUDED__;