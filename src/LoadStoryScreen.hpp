// The main game

// Include guard
#ifndef __LoadStoryScreen_H_INCLUDED__
#define __LoadStoryScreen_H_INCLUDED__

#include <memory>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include "GameSlice.hpp"
#include "MainGame.hpp"
#include "GlobalSettings.hpp"
#include "TextHandler.hpp"

namespace StoryTime {

class LoadStoryScreen: public GameSlice
{
  public:
    // Constructor
    LoadStoryScreen();

    // React to input
    virtual void takeInput(sf::Event& curEvent, sf::RenderWindow& renderWindow);

    // Do a single frame update and return a pointer which is NULL if no change, else a pointer to a new slice
    virtual GameSlice* update(sf::Time& elapsedTime, sf::RenderWindow& renderWindow);

    // Draw the slice
    virtual void draw(sf::RenderWindow& renderWindow);

    // Get the background colour
    virtual sf::Color& getBackgroundColour();

    // This ensures something something about pointers so a memory thing
    virtual ~LoadStoryScreen();
  private:
    
    // Inhereted from parent
    // bool _changeSlice;
    // sf::Color _backgroundColour;

    // Not inhereted
    sf::Text _titleText;
    std::vector<sf::Text> _storyChoices;
    sf::Sprite _windowBorder;
    sf::Texture _borderTexture;
    std::filesystem::path _storyPath;
};


} // End namespace StoryTime


#endif // __LoadStoryScreen_H_INCLUDED__;