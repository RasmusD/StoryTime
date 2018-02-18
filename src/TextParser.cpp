#include "TextParser.hpp"

namespace StoryTime {

void TextParser::parseText(std::string& text,
                          std::deque<Utils::SegChoice>& segments)
{
  // Active markup settings
  Markup activeMarkup = Markup();
  // Are we parsing a markup tag? Not whether one is open, but whether we're parsing one.
  bool parsingMarkup = false;
  // Current chunk of text parsed before any markup detection
  std::string chunk;
  std::string possibleMarkup;
  // Valid markup
  std::unordered_map<std::string, std::pair<std::unordered_set<std::string>, std::string> > validMarkup = getValidMarkup();
  for (char c : text)
  {
    if (c == '<')
    {
      possibleMarkup += c;
      if (parsingMarkup == false)
      {
        // If there may be some markup
        parsingMarkup = true;
      } else {
        // If we are already parsing markup this is considered an error
        // We then assume this to be ill-formed and should be spoken
        chunk += possibleMarkup;
        possibleMarkup.clear();
        parsingMarkup = false;
      }

    } else if (c == '>' && parsingMarkup == true)
    {
      possibleMarkup += c;
      // Add the current chunk
      // although the markup may be invalid at this point
      // we always split tokens at '>' anyway so this is safe
      //std::cout << "For sent (" << utterance << ") I'm adding:" << std::endl;
      //std::cout << chunk << std::endl;
      std::unique_ptr<TextSegment> seg(new TextSegment(GlobalSettings::DEFAULTFONT, chunk, GlobalSettings::DEFAULTTEXTSPEED));
      segments.push_back(Utils::SegChoice());
      segments.back().text = std::move(seg);
      chunk.clear();
      // Identify markup will add the markup to the currently active markup
      // and ignore well-formed but unsupported markup
      // so we only need to do something if the markup is invalid
      // namely we assume this should be spoken
      if (identifyMarkup(possibleMarkup, activeMarkup, segments, validMarkup) != true)
      {
        chunk += possibleMarkup;
      }
      // Reset the possible markup
      possibleMarkup.clear();
      // If we should close a markup tag
      parsingMarkup = false;
    } else if (parsingMarkup == true) {
      possibleMarkup += c;
    } else {
      chunk += c;
    }
  }

  // If we have an unclosed tag
  if (possibleMarkup.empty() == false)
  {
    chunk += possibleMarkup;
  }
  if (chunk.empty() == false)
  {
    //std::cout << "For sent (" << text << ") I'm adding:" << std::endl;
    //std::cout << chunk << std::endl;
    std::unique_ptr<TextSegment> seg(new TextSegment(GlobalSettings::DEFAULTFONT, chunk, GlobalSettings::DEFAULTTEXTSPEED));
    segments.push_back(Utils::SegChoice());
    segments.back().text = std::move(seg);
    chunk.clear();
  }
}


bool TextParser::identifyMarkup(std::string possibleMarkup,
                                Markup& activeMarkup,
                                std::deque<Utils::SegChoice>& segments,
                                std::unordered_map<std::string, std::pair<std::unordered_set<std::string>, std::string> >& validMarkup)
{
  // Is this an opening, closing or self-contained piece of markup?
  //std::cout << possibleMarkup << std::endl;
  //std::cout << possibleMarkup.substr(0, 2) << std::endl;
  if (possibleMarkup.substr(0, 2) == "</")
  {
    return closeMarkup(possibleMarkup,
                      activeMarkup,
                      segments,
                      validMarkup);
  } else {
    return openMarkup(possibleMarkup,
                      activeMarkup,
                      segments,
                      validMarkup);
  }
}


bool TextParser::closeMarkup(std::string possibleMarkup,
                            Markup& activeMarkup,
                            std::deque<Utils::SegChoice>& segments,
                            std::unordered_map<std::string, std::pair<std::unordered_set<std::string>, std::string> >& validMarkup)
{
  std::string type;
  //std::cout << "Trying to close " << possibleMarkup << std::endl;
  // We skip the initial </ so start at 2
  for (int i = 2; i < possibleMarkup.size(); i++)
  {
    char cChar = possibleMarkup.at(i);
    if (cChar == '>')
    {
      if (validMarkup.count(type) > 0)
      {
        // Iterate from the back of the activeMarkup and try and find the type
        // TODO make reverse_iterator
        for (int i = activeMarkup.activeMarkup.size() - 1; i >= 0; i--)
        {
          std::tuple<std::string, std::string, std::string> cMarkup = activeMarkup.activeMarkup.at(i);
          /*std::cout << type << std::endl;
          std::cout << std::get<0>(cMarkup) << std::endl;
          std::cout << std::get<1>(cMarkup) << std::endl;
          std::cout << std::get<2>(cMarkup) << std::endl;*/
          if (std::get<0>(cMarkup) == type)
          {
            // Set the markup to its previous value
            if (type == "test")
            {
              if (std::get<1>(cMarkup) == "val")
              {
                activeMarkup.test = std::get<2>(cMarkup);
              } else {
                std::cerr << "TextParser: Unknown subtype (" + std::get<1>(cMarkup) + ") for markup type (" + type + "). How did this even happen?" << std::endl;
                return false;
              }
            } else if (type == "test2")
            {
              if (std::get<1>(cMarkup) == "val")
              {
                activeMarkup.test2 = std::stod(std::get<2>(cMarkup));
              } else {
                std::cerr << "TextParser: Unknown subtype (" + std::get<1>(cMarkup) + ") for markup type (" + type + "). How did this even happen?" << std::endl;
                return false;
              }
            } else if (type == "ignore") {
              // Just ignore it
            } else {
              std::cerr << "TextParser: Unknown markup (" + type + "). How did this even happen?" << std::endl;
              return false;
            }
            activeMarkup.activeMarkup.erase(activeMarkup.activeMarkup.begin()+i);
            return true;
          }
        }
        // If we haven't returned by now the type is not active
        std::cerr << "TextParser: " + possibleMarkup + " is not currently active markup." << std::endl;
        return false;
      } else {
        std::cerr << "TextParser: " + type + " is not a recognised markup type." << std::endl;
        return false;
      }
    } else {
      type += cChar;
    }
  }
  
  std::cerr << "TTSMarkup: " + possibleMarkup + " is not valid markup." << std::endl;
  return false;
}

bool TextParser::openMarkup(std::string possibleMarkup,
                            Markup& activeMarkup,
                            std::deque<Utils::SegChoice>& segments,
                            std::unordered_map<std::string, std::pair<std::unordered_set<std::string>, std::string> >& validMarkup)
{
  bool foundType = false;
  std::pair<std::string, std::pair<std::unordered_set<std::string>, std::string> > type;
  bool foundSubtype = false;
  std::string subtype;
  bool foundValue = false;
  bool foundApostrophe = false;
  std::string value;
  std::string chunk;
  // We skip the initial < so start at 1
  for (int i = 1; i < possibleMarkup.size(); i++)
  {
    char cChar = possibleMarkup.at(i);
    if (foundType == false)
    {
      if (cChar == ' ')
      {
        auto typeIt = validMarkup.find(chunk);
        if (typeIt != validMarkup.end())
        {
          type = *typeIt;
          foundType = true;
          chunk.clear();
        } else {
          std::cerr << "TextParser: " + possibleMarkup + " has an unsupported type (" + chunk + ")." << std::endl;
          return false;
        }
      }  else if (cChar == '>')
      {
        // If this is a type and it should not take any subtype break the loop
        //std::cout << chunk << std::endl;
        // We lower case the chunk for case insensitivity
        auto typeIt = validMarkup.find(chunk);
        if (typeIt != validMarkup.end() && typeIt->second.second == "")
        {
          foundType = true;
          type = *typeIt;
          foundSubtype = true;
          foundValue = true;
          chunk = cChar;
          break;
        } else {
          std::cerr << "TextParser: " + possibleMarkup + " is not a unsupported type." << std::endl;
          return false;
        }
      } else {
        chunk += cChar;
      }
    } else if (foundSubtype == false) {
      if (cChar == '=')
      {
        // We lower case the chunk for case insensitivity
        subtype = chunk;
        if (type.second.first.count(subtype) > 0)
        {
          foundSubtype = true;
          chunk.clear();
        } else {
          std::cerr << "TextParser: " + possibleMarkup + " has an unsupported subtype (" + subtype + ")." << std::endl;
          return false;
        }
      } else {
        chunk += cChar;
      }
    } else if (foundValue == false) {
      //std::cout << "Having found type and subtype chunk is now: " << chunk << " and cChar is: " << cChar << std::endl;
      if (cChar == '\"' || cChar == '\'')
      {
        // If chunk is empty and an apostrophe has not been found
        // Set the apostrophe to be found (this is the opening one)
        // If an apostrophe has been found the current one may be the end
        if (chunk.empty() == true && foundApostrophe == false)
        {
          foundApostrophe = true;
        } else if (foundApostrophe == true)
        {
          // If this has not been escaped it is the end
          if (possibleMarkup.at(i-1) != '\\')
          {
            value = chunk;
            foundValue = true;
            chunk.clear();
          } else {
            chunk += cChar;
          }
        } else {
          std::cerr << "TextParser: I found no opening apostrophe for the value in " + possibleMarkup + " this is ill-formed." << std::endl;
          return false;
        }
      } else {
        chunk += cChar;
      }
    } else {
      chunk += cChar;
    }
  }

  // If the remaining chunk is not > or /> there is something wrong
  // Remove potential whitespace
  if (chunk.front() == ' ')
  {
    chunk.erase(chunk.begin());
  }
  //std::cout << chunk << std::endl;
  if (chunk != ">" && chunk != "/>")
  {
    std::cerr << "TextParser: " + possibleMarkup + " seems malformed." << std::endl;
    return false;
  }

  if (foundValue == true)
  {
    return applyMarkup(type, subtype, value, activeMarkup, segments);
  } else {
    std::cerr << "TextParser: " + possibleMarkup + " did not have a value (" + chunk + ")." << std::endl;
    return false;
  }
}


bool TextParser::applyMarkup(std::pair<std::string, std::pair<std::unordered_set<std::string>, std::string> >& type,
                                std::string subtype,
                                std::string value,
                                Markup& activeMarkup,
                                std::deque<Utils::SegChoice>& segments)
{
  //std::cout << value << std::endl;
  // Ready for use the activemarkup tuple
  std::tuple<std::string, std::string, std::string> cMark;
  std::get<0>(cMark) = type.first;
  std::get<1>(cMark) = subtype;
  // This is changing depending on the markup
  // Remember to set it!
  std::get<2>(cMark) = "";
  if (type.second.second == "double")
  {
    if (type.first == "test2")
    {
      if (subtype == "val")
      {
        try
        {
          std::get<2>(cMark) = std::to_string(activeMarkup.test2);
          activeMarkup.test2 = std::stod(value);
        }
        catch (...)
        {
          std::cerr << "TextParser: Could not convert " + value + " to double which is required for markup of type (" + type.first + ")." << std::endl;
          return false;
        }
      } else {
        std::cerr << "TextParser: I somehow got markup of subtype (" + subtype + ") but it's unsupported for type (" + type.first + ")." << std::endl;  
        return false;
      }
      activeMarkup.activeMarkup.push_back(cMark);
      return true;
    } else {
      std::cerr << "TextParser: I somehow got markup of type (" + type.first + ") but it's unsupported!" << std::endl;  
      return false;
    }
  } else if (type.second.second == "string") {
    if (type.first == "test")
    {
      // Check if this is a self-contained tag or not
      if (subtype == "val")
      {
        std::get<2>(cMark) = activeMarkup.test;
        activeMarkup.test = value;
        activeMarkup.activeMarkup.push_back(cMark);
      } else {
        std::cerr << "TextParser: I somehow got markup of subtype (" + subtype + ") but it's unsupported for type (" + type.first + ")." << std::endl;  
        return false;
      }
      return true;
    } else if (type.first == "choice")
    {
      // Check if this is a self-contained tag or not
      if (subtype == "def")
      {
        addChoice(segments, value);
      } else {
        std::cerr << "TextParser: I somehow got markup of subtype (" + subtype + ") but it's unsupported for type (" + type.first + ")." << std::endl;  
        return false;
      }
      return true;
    } else {
      std::cerr << "TextParser: I somehow got markup of type (" + type.first + ") but it's unsupported!" << std::endl;
      return false;
    }
  } else if (type.second.second == "")
  {
    if (value != "")
    {
      std::cerr << "TextParser: Got value (" + value + ") for self-contained markup (" + type.first + ") which should have none. Applying markup ignoring value...\n" << std::endl;
    }
    if (type.first == "ignore")
    {
      // Nothing to do but consume markup and register the tag as active
      activeMarkup.activeMarkup.push_back(cMark);
      return true;
    } else {
      std::cerr << "TextParser: I somehow got markup of type (" + type.first + ") but it's unsupported!" << std::endl;
      return false;
    }
  } else {
    std::cerr << "TextParser: " + value + " is invalid for markup of type " + type.first + "."<< std::endl;
    return false;
  }
}

void TextParser::addChoice(std::deque<Utils::SegChoice>& segments, std::string& value)
{
  std::vector<std::pair<std::string, int>> choiceVec;

  // Split on -
  std::stringstream stream(value);
  std::string segment;
  while (std::getline(stream, segment, '-'))
  {
    std::pair<std::string, int> choice;
    // Split on /
    std::stringstream cStream;
    cStream << segment;
    // Should have exactly two things to look at
    std::string choiceText;
    std::getline(cStream, choiceText, '/');
    choice.first = choiceText;
    std::getline(cStream, choiceText, '/');
    try
    {
      choice.second = std::stoi(choiceText);
    } catch(...) {
      throw std::runtime_error("TextParser: Cannot convert " + choiceText + " to int.");
    }
    choiceVec.push_back(choice);
  }

  if (choiceVec.size() == 0)
  {
    throw std::runtime_error("TextParser: Didn't find any choices in choice markup! Def: " + value);
  } else {
    sf::Vector2f pos(0.f, 0.f);
    std::unique_ptr<ChoiceBox> cB(new ChoiceBox(GlobalSettings::DEFAULTFONT, choiceVec, pos));
    segments.push_back(Utils::SegChoice());
    segments.back().choice = std::move(cB);
  }
}

/*
A map of valid markup types.
The key is the markup type name.
The value a pair containing a vector of valid subtypes and a string describing accepted value types
The possible accepted value types is "double" and "string"
If the set of valid subtypes is empty this means the markup is self-contained
NOTE: If you add a valid markup tag here it should also be added to the applyMarkup function, closeMarkup if appropriate,
the equality operator if appropriate and its actual funtionality implemented where appropriate.
*/
std::unordered_map<std::string, std::pair<std::unordered_set<std::string>, std::string> > TextParser::getValidMarkup()
{
  std::unordered_map<std::string, std::pair<std::unordered_set<std::string>, std::string> > validMarkup;
  std::pair<std::string, std::pair<std::unordered_set<std::string>, std::string> > tag;
  // A tag for demonstrating a sstring
  tag = {"test", {{"val"}, "string"}};
  validMarkup.insert(tag);
  // A tag demonstrating a double
  tag = {"test2", {{"val"}, "double"}};
  validMarkup.insert(tag);
  // A standard choice
  tag = {"choice", {{"def"}, "string"}};
  validMarkup.insert(tag);
  // A tag to be ignored
  tag = {"ignore", {{""}, ""}};
  // For some reason I can't leave that empty in a statin method according to g++4.9 so we create it with something and then clear it
  tag.second.first.clear();
  validMarkup.insert(tag);
  return validMarkup;
}

} // End namespace StoryTime