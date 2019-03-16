#include "StoryResources.hpp"

namespace StoryTime {

StoryResources::StoryResources(const std::filesystem::path& storyDirectory,
                              const std::unordered_set<std::string>& imageNames)
{
  // Load images
  for (auto& imgNam : imageNames)
  {
    if (addImage(storyDirectory, imgNam) == false)
    {
      throw;
    }
  }
}

bool StoryResources::addImage(const std::filesystem::path& storyDirectory,
                              const std::string& imageName)
{
  sf::Texture img;
  std::filesystem::path imgStrPth = storyDirectory / "images" / imageName;
  std::filesystem::path imgResPth = std::filesystem::current_path() / "resources" / "images" / imageName;

  if (_images.find(imgStrPth.filename()) != _images.end())
  {
    std::cout << "Duplicate image name - already loaded - " << imgStrPth.filename() << std::endl;
    return true;
  }

  if (img.loadFromFile(imgStrPth.string()))
  {
    _images.insert({imgStrPth.filename(), img}); 
  } else if (img.loadFromFile(imgResPth.string()))
  {
    _images.insert({imgResPth.filename(), img}); 
  } else {
    std::cout << "Could not load image " << imgStrPth.filename() << std::endl;
    return false;
  }

  return true;
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