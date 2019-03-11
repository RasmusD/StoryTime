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

    // React to input
    virtual void takeInput(sf::Event& curEvent, sf::RenderWindow& renderWindow) {};

    // Do a single frame update and return a pointer which is nullptr if no change, else a pointer to a new slice
    virtual GameSlice* update(sf::Time& elapsedTime, sf::RenderWindow& renderWindow) { return nullptr; };

    // Draw the slice
    virtual void draw(sf::RenderWindow& renderWindow) {};

    // Get the background colour of the slice
    virtual sf::Color& getBackgroundColour() {return _backgroundColour;};

    // This ensures something something about pointers so a memory thing
    virtual ~GameSlice() {};
  protected:
    bool _changeSlice;
    sf::Color _backgroundColour;
};


} // End namespace StoryTime


#endif // __GameSlice_H_INCLUDED__;