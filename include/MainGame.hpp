// The main game

// Include guard
#ifndef __MainGame_H_INCLUDED__
#define __MainGame_H_INCLUDED__

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "GameSlice.hpp"
#include "GlobalSettings.hpp"
#include "MenuScreen.hpp"
#include "TextHandler.hpp"
#include "TextSegment.hpp"
#include "ChoiceBox.hpp"

namespace StoryTime {

class MainGame: public GameSlice
{
  public:
    // Constructor
    MainGame();

    // React to input
    virtual void takeInput(sf::Event& curEvent, sf::RenderWindow& renderWindow);

    // Do a single frame update and return a pointer which is NULL if no change, else a pointer to a new slice
    virtual GameSlice* update(sf::Time& elapsedTime, sf::RenderWindow& renderWindow);

    // Draw the slice
    virtual void draw(sf::RenderWindow& renderWindow);

    // This ensures something something about pointers so a memory thing
    virtual ~MainGame();
  private:
    std::unique_ptr<TextHandler> _gameText;
    ChoiceBox _choice;

    float _timeCount;
    
    // Inhereted from parent
    // bool _changeSlice;
};


} // End namespace StoryTime


#endif // __GameSlice_H_INCLUDED__;