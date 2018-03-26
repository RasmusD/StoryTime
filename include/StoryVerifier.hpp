// A tool for verifying the correctness of a story

// Include guard
#ifndef __StoryVerifier_H_INCLUDED__
#define __StoryVerifier_H_INCLUDED__

#include "TextParser.hpp"

namespace StoryTime {

class StoryVerifier
{
  public:
    // Verify if a story is valid
    static bool verifyStory(std::unordered_map<std::string, std::string>& storyData);
  private:
    // Verify if a set of paths all lead to [end]
    static bool verifyPaths(std::unordered_map<std::string, std::vector<std::string>>& paths,
                            std::string& startKey,
                            std::unordered_set<std::string> history);
};


} // End namespace StoryTime


#endif // __StoryVerifier_H_INCLUDED__;