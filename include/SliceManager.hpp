// An empty base class for game slices

// Include guard
#ifndef __SliceManager_H_INCLUDED__
#define __SliceManager_H_INCLUDED__

#include <iostream>

namespace StoryTime {

class SliceManager
{
  public:
    // Current GameSlice
    GameSlice currScene;

    // React to user input
    virtual void react(sf::Event& event) {};

    // Do a single frame update and return a pointer which is NULL if no change, else a pointer to a new slice
    virtual SliceManager* update(sf::Time& elapsedTime) {};

    // Draw the slice
    virtual void draw(sf::RenderWindow& renderWindow) {};

    // This ensures something something about pointers so a memory thing
    virtual ~SliceManager() {};
  private:

    static SliceManager instance;
};


} // End namespace StoryTime


#endif // __SliceManager_H_INCLUDED__;