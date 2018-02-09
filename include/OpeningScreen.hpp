// A class for game slices

// Include guard
#ifndef __OpeningScreen_H_INCLUDED__
#define __OpeningScreen_H_INCLUDED__

#include <iostream>

#include "GameSlice.hpp"
#include "MenuScreen.hpp"
#include "GlobalSettings.hpp"

namespace StoryTime {

class OpeningScreen: public GameSlice
{
  public:
    // Constructor
    OpeningScreen();

    // Destructor
    ~OpeningScreen() {};

    // Do a single frame update and return a pointer which is NULL if no change, else a pointer to a new slice
    virtual GameSlice* update(sf::Time& elapsedTime, sf::Event& curEvent, sf::Event& prevEvent, sf::RenderWindow& renderWindow);

    // Draw the screen
    virtual void draw(sf::RenderWindow& renderWindow);

  private:
    sf::Font _titleFont;
    sf::Text _titleText;
    sf::FloatRect _titleTextRect;
};


} // End namespace StoryTime


#endif // __OpeningScreen_H_INCLUDED__;