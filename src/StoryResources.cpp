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
    sf::Image img;
    if (img.loadFromFile(imgStrPth.string()))
    {
      if (_images.find(imgStrPth.stem()) != _images.end())
      {
        std::cout << "Duplicate image name " << imgNam << std::endl;
        throw;
      }
      _images.insert({imgStrPth.stem(), img}); 
    } else if (img.loadFromFile(imgResPth.string())) {
      if (_images.find(imgResPth.stem()) != _images.end())
      {
        std::cout << "Duplicate image name " << imgNam << std::endl;
        throw;
      }
      _images.insert({imgResPth.stem(), img});
    } else {
      std::cout << "Could not load image " << imgNam << std::endl;
      throw;
    }
  }
}

sf::Image StoryResources::getImageCopy(const std::string& imageName)
{
  return _images[imageName];
}

sf::Image& StoryResources::getImageRef(const std::string& imageName)
{
  return std::ref(_images[imageName]);
}

} // End namespace StoryTime