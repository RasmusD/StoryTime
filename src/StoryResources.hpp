// A set of resources to use in a story
// Generally loaded on story load to reduce chance of crashes while running
// Also increases memory use but decreases chance of fps drop

#ifndef __StoryResources_H_INCLUDED__
#define __StoryResources_H_INCLUDED__

#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <unordered_set>

#include <SFML/Graphics.hpp>

namespace StoryTime {

class StoryResources
{
  public:
    // Constructor
    // TODO should also load fonts
    StoryResources(const std::filesystem::path& storyDirectory,
                    const std::unordered_set<std::string>& imageNames);
    StoryResources() {};

    // Destructor
    ~StoryResources() {};

    // Get an image copy
    sf::Image getImageCopy(const std::string& imageName);

    // Get an image reference
    sf::Image& getImageRef(const std::string& imageName);

  private:
    std::unordered_map<std::string, sf::Image> _images;
};


} // End namespace StoryTime


#endif // __StoryResources_H_INCLUDED__;