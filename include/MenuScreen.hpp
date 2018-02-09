// A class for game slices

// Include guard
#ifndef __MenuScreen_H_INCLUDED__
#define __MenuScreen_H_INCLUDED__

#include <iostream>

#include "Utils.hpp"
#include "MainGame.hpp"
#include "GameSlice.hpp"
#include "GlobalSettings.hpp"

namespace StoryTime {

class MenuScreen: public GameSlice
{
  public:
    // Constructor
    MenuScreen();

    // Destructor
    ~MenuScreen() {};

    // Do a single frame update and return a pointer which is NULL if no change, else a pointer to a new slice
    virtual GameSlice* update(sf::Time& elapsedTime, sf::Event& curEvent, sf::Event& prevEvent, sf::RenderWindow& renderWindow);

    // Draw the screen
    virtual void draw(sf::RenderWindow& renderWindow);

  private:
    sf::Font _titleFont;
    sf::Text _titleText;
    sf::Text _newgameText;

    sf::FloatRect _textRect;
};


} // End namespace StoryTime


#endif // __MenuScreen_H_INCLUDED__;