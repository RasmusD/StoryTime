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
    /*
    Load a story and verify if it is valid
    stroyPath = path to story file
    storyData = the output of the final story elements
    print = whetehr to print details of the verification or not
    strictVerification = if true the verification process may fail even if all paths from [begin] is valid. E.g. if there are branches which are unreachable.
    */
    static bool loadAndVerifyStory(std::string storyPath,
                                  std::unordered_map<std::string, std::string>& storyData,
                                  bool print,
                                  bool strictVerification);
  private:
    /*
    Verify if a set of paths all lead to [end]
    paths = the set of from/to paths
    startKey = the starting path for the verification
    history = the history of the current path being checked. Passed as copy to give each token individual history
    pathsTouched = a set of touched path keys which have been reached used to verify if all paths are reachable
    print = whether to print verification progress
    */
    static bool verifyPaths(std::unordered_map<std::string, std::vector<std::string>>& paths,
                            std::string& startKey,
                            std::unordered_set<std::string> history,
                            std::unordered_set<std::string>& pathsTouched,
                            bool print);
};


} // End namespace StoryTime


#endif // __StoryVerifier_H_INCLUDED__;