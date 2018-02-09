#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "GameSlice.hpp"
#include "OpeningScreen.hpp"
#include "GlobalSettings.hpp"

namespace StoryTime {

struct Game
{
  // Create game window
  sf::RenderWindow window{{GlobalSettings::WINDOWWIDTH, GlobalSettings::WINDOWHEIGHT}, "StoryTime"};

  bool running{false};

  sf::Clock clock;

  sf::Time elapsedTime;

  GameSlice* currentSlice = new OpeningScreen();
  // Keeps track of any changes in slice
  GameSlice* changeSlice = NULL;

  sf::Event curEvent;
  sf::Event prevEvent;

  Game()
  {
    window.setFramerateLimit(60);
  }

  void run()
  {
    running = true;

    // Restart the clock
    clock.restart();

    while (running == true)
    {
      elapsedTime = clock.restart();

      inputPhase();
      updatePhase();
      drawPhase();

      window.setTitle("StoryTime");
    }
  }

  void inputPhase()
  {
    while(window.pollEvent(curEvent))
    {
      switch (curEvent.type)
      {
        case sf::Event::Closed:
          window.close();
          running = false;
          break;
        // If escape is pressed exit the game
        case sf::Event::KeyPressed:
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
          {
            running = false;
          }
          break;
        default:
          break;
      }
    }
  }

  void updatePhase()
  {
    // Logic Updates
    changeSlice = currentSlice->update(elapsedTime, curEvent, prevEvent, window);

    // If changeSlice is not null delete the old and make that the new current
    if (changeSlice != NULL)
    {
      delete currentSlice;
      currentSlice = changeSlice;
      changeSlice = NULL;
    }

    // Because of the way we do this - this is ok
    prevEvent = curEvent;
  }

  void drawPhase()
  {
    // Draw things
    // "Clear" window from previous frame
    window.clear(sf::Color::Black);

    // Do drawing
    currentSlice->draw(window);

    // Show window
    window.display();
  }
};

} // End namespace StoryTime


int main()
{

  StoryTime::Game{}.run();

  return 0;
}