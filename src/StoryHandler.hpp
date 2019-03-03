// The main game

// Include guard
#ifndef __StoryHandler_H_INCLUDED__
#define __StoryHandler_H_INCLUDED__

#include <memory>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include "GameSlice.hpp"
#include "GlobalSettings.hpp"
#include "MenuScreen.hpp"
#include "TextBox.hpp"
#include "TextSegment.hpp"
#include "ChoiceBox.hpp"
#include "StoryVerifier.hpp"
#include "GameSaver.hpp"
#include "StoryResources.hpp"

namespace StoryTime {

class StoryHandler: public GameSlice
{
  public:
    // Constructor
    StoryHandler(std::filesystem::path& storyPath, bool storyIsSave);

    // React to input
    virtual void takeInput(sf::Event& curEvent, sf::RenderWindow& renderWindow);

    // Do a single frame update and return a pointer which is NULL if no change, else a pointer to a new slice
    virtual GameSlice* update(sf::Time& elapsedTime, sf::RenderWindow& renderWindow);

    // Draw the slice
    virtual void draw(sf::RenderWindow& renderWindow);

    // Get the background colour
    virtual sf::Color& getBackgroundColour();

    // This ensures something something about pointers so a memory thing
    virtual ~StoryHandler();
  private:
    // Methods
    void _setNextSegment();
    void _setTextNext();
    void _setChoiceNext();

    // Add a new branch
    void _addBranch(std::string& id);

    // A set of resources used in this story
    StoryResources _resources;

    // Dictionary of branching story segments
    std::unordered_map<std::string, std::string> _storyData;

    // List of previously made choices
    std::unordered_set<std::string> _choiceHistory;

    // Current segment id in the story
    std::string _currentSegmentId;

    // Ordered list of TextSegments and ChoiceBoxes to go through
    std::deque<Utils::SegChoice> _segmentQueue;

    // Current choice
    std::unique_ptr<ChoiceBox> _currentChoice;
    
    // Are we currently making a choice?
    bool _choiceActive;
    
    // Should the next segment be a choice or text?
    bool _isNextChoice;

    // Main story text box
    std::unique_ptr<TextBox> _gameText;

    // Choice box
    std::unique_ptr<ChoiceBox> _choiceBox;

    sf::Sprite _windowBorder;
    sf::Texture _borderTexture;

    float _timeCount;

    Markup _gameDefaults;

    std::filesystem::path _storyPath;
    
    // Inhereted from parent
    // bool _changeSlice;
};


} // End namespace StoryTime


#endif // __GameSlice_H_INCLUDED__;