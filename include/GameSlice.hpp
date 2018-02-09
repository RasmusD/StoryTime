// An empty base class for game slices

// Include guard
#ifndef __GameSlice_H_INCLUDED__
#define __GameSlice_H_INCLUDED__

#include <iostream>

#include <SFML/Graphics.hpp>

namespace StoryTime {

class GameSlice
{
  public:
    // Constructor
    GameSlice();

    // Do a single frame update and return a pointer which is NULL if no change, else a pointer to a new slice
    virtual GameSlice* update(sf::Time& elapsedTime, sf::Event& curEvent, sf::Event& prevEvent, sf::RenderWindow& renderWindow) { return NULL; };

    // Draw the slice
    virtual void draw(sf::RenderWindow& renderWindow) {};

    // This ensures something something about pointers so a memory thing
    virtual ~GameSlice() {};
};


} // End namespace StoryTime


#endif // __GameSlice_H_INCLUDED__;