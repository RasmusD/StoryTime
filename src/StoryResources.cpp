#include "StoryResources.hpp"

namespace StoryTime {

StoryResources::StoryResources(const std::filesystem::path& storyDirectory,
                              const std::unordered_set<std::string>& imageNames)
{
  // Load images
  for (auto& imgNam : imageNames)
  {
    std::filesystem::path imgStrPth = storyDirectory / "images" / imgNam;
    std::filesystem::path imgResPth = std::filesystem::current_path() / "resources" / "images" / imgNam;
    sf::Texture img;
    if (img.loadFromFile(imgStrPth.string()))
    {
      if (_images.find(imgStrPth) != _images.end())
      {
        std::cout << "Duplicate image name " << imgNam << std::endl;
        throw;
      }
      _images.insert({imgStrPth.filename(), img}); 
    } else if (img.loadFromFile(imgResPth.string())) {
      if (_images.find(imgResPth) != _images.end())
      {
        std::cout << "Duplicate image name " << imgNam << std::endl;
        throw;
      }
      _images.insert({imgResPth.filename(), img});
    } else {
      std::cout << "Could not load image " << imgNam << std::endl;
      throw;
    }
  }
}

sf::Texture StoryResources::getImageCopy(const std::string& imageName)
{
  if (_images.count(imageName) == 1)
  {
    return _images[imageName];
  } else {
    std::cout << "Requested image does not exist. Returning empty image." << std::endl;
    return sf::Texture();
  }
}

const sf::Texture* StoryResources::getImagePtr(std::string imageName)
{
  if (_images.count(imageName) == 1)
  {
    return &_images[imageName];
  } else {
    std::cout << "Requested image (" << imageName << ") does not exist. Returning nullptr." << std::endl;
    for (auto& img : _images)
    {
      std::cout << img.first << std::endl;
    }
    return nullptr;
  }
}

} // End namespace StoryTime