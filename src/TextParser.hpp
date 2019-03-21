// The main game

// Include guard
#ifndef __TextParser_H_INCLUDED__
#define __TextParser_H_INCLUDED__

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <deque>

#include <SFML/Graphics.hpp>

#include "GlobalSettings.hpp"
#include "Utils.hpp"

namespace StoryTime {

class TextParser
{
  public:
    // Constructor
    TextParser();

    // Destuctor
    ~TextParser() {};

    // Parse a story segment
    static void parseText(const std::string& text, std::deque<Utils::SegChoice>& segments, Markup& activeMarkup);

    // Parse a settings string
    static void parseSettings(Markup& currentSettings, std::string& settingsString);
  private:
    // Find if possibleMarkup is valid markup and apply if it is supported
    static bool identifyMarkup(std::string possibleMarkup,
                                Markup& activeMarkup,
                                std::deque<Utils::SegChoice>& segments, 
                                std::unordered_map<std::string, std::pair<std::unordered_set<std::string>, std::string> >& validMarkup);
    // Find and apply a markup tag closing (</colour>)
    // Returns false if no markup of type is currently open, type is not supported (</imaginary>) or is malformed (</imaginary stuff>)
    static bool closeMarkup(std::string possibleMarkup,
                            Markup& activeMarkup,
                            std::deque<Utils::SegChoice>& segments, 
                            std::unordered_map<std::string, std::pair<std::unordered_set<std::string>, std::string> >& validMarkup);
    // Find and apply a markup tag opening (<colour val="black">)
    // Returns false if type is not supported (<imaginary stuff="bla">) or markup is malformed (<colour val=="black">)
    static bool openMarkup(std::string possibleMarkup,
                            Markup& activeMarkup,
                            std::deque<Utils::SegChoice>& segments,
                            std::unordered_map<std::string, std::pair<std::unordered_set<std::string>, std::string> >& validMarkup);
    
    /*
    Apply a markup tag. Note this must only be called by identifyMarkup, closeMarkup and openMarkup
    as these check if the markup is valid and supported and this only checks if the given value is valid.
    */
    static bool applyMarkup(std::pair<std::string, std::pair<std::unordered_set<std::string>, std::string> >& type,
                            std::string subtype,
                            std::string value,
                            Markup& activeMarkup,
                            std::deque<Utils::SegChoice>& segments);
    
    // Add a found choice
    static void addBranchChoice(std::deque<Utils::SegChoice>& segments,
                                std::string& value,
                                Markup& activeMarkup);
    static void addValueChoice(std::deque<Utils::SegChoice>& segments,
                                std::string& value,
                                Markup& activeMarkup);
    // Add a text variant
    static void addOptionalText(std::deque<Utils::SegChoice>& segments,
                                std::string& value,
                                Markup& activeMarkup);
    static void addVariantText(std::deque<Utils::SegChoice>& segments,
                                std::string& value,
                                Markup& activeMarkup);

    // Get a colour from a markup string
    static sf::Color getColourFromString(std::string& rgbaString);
    static std::string getColourStringFromSFColor(sf::Color& colour);

    /*
    A map of valid markup types.
    The key is the markup type name.
    The value a pair containing a vector of valid subtypes and a string describing accepted value types
    The possible accepted value types is "double" and "string"
    If the set of valid subtypes is empty this means the markup is self-contained
    NOTE: If you add a valid markup tag here it should also be added to the applyMarkup function, closeMarkup if appropriate,
    the equality operator if appropriate and its actual funtionality implemented where appropriate.
    */
    static std::unordered_map<std::string, std::pair<std::unordered_set<std::string>, std::string> > getValidMarkup();
};


} // End namespace StoryTime


#endif // __TextParser_H_INCLUDED__;