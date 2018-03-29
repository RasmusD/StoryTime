// A tool for verifying the correctness of a story

// Include guard
#ifndef __StoryVerifier_H_INCLUDED__
#define __StoryVerifier_H_INCLUDED__

#include <iostream>
#include <fstream>

#include "TextParser.hpp"

namespace StoryTime {

class StoryVerifier
{
  public:
    // Load a story and verify if it is valid
    static bool loadAndVerifyStory(std::string storyPath, std::unordered_map<std::string, std::string>& storyData, bool print);
  private:
    // Verify if a set of paths all lead to [end]
    static bool verifyPaths(std::unordered_map<std::string, std::vector<std::string>>& paths,
                            std::string& startKey,
                            std::unordered_set<std::string> history,
                            bool print);
};


} // End namespace StoryTime


#endif // __StoryVerifier_H_INCLUDED__;