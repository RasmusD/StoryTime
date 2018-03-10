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
      std::unique_ptr<TextSegment> seg(new TextSegment(GlobalSettings::DEFAULTFONT, chunk, GlobalSettings::DEFAULTTEXTSPEED, activeMarkup));
      segments.push_back(Utils::SegChoice());
      segments.back().text = std::move(seg);
      chunk.clear();
      // Identify markup will add the markup to the currently active markup
      // and ignore well-formed but unsupported markup
      // so we only need to do something if the markup is invalid
      //std::cout << possibleMarkup << std::endl;
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
    } else if (c == '\n') {
      chunk += c;
      // Separate on new line
      std::unique_ptr<TextSegment> seg(new TextSegment(GlobalSettings::DEFAULTFONT, chunk, GlobalSettings::DEFAULTTEXTSPEED, activeMarkup));
      segments.push_back(Utils::SegChoice());
      segments.back().text = std::move(seg);
      chunk.clear();
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
    std::unique_ptr<TextSegment> seg(new TextSegment(GlobalSettings::DEFAULTFONT, chunk, GlobalSettings::DEFAULTTEXTSPEED, activeMarkup));
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
            if (type == "font")
            {
              if (std::get<1>(cMarkup) == "colour")
              {
                activeMarkup.colour = getColourFromString(std::get<2>(cMarkup));
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
      } else if (cChar == '>')
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
      //std::cout << "check - " << chunk << std::endl;
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
            // Add character, but remove escape
            chunk.pop_back();
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
    //std::cout << value << std::endl;
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
    if (type.first == "font")
    {
      // Check if this is a self-contained tag or not
      if (subtype == "colour")
      {
        // Store previous value
        std::get<2>(cMark) = getColourStringFromSFColor(activeMarkup.colour);
        activeMarkup.activeMarkup.push_back(cMark);
        // Set new value
        activeMarkup.colour = getColourFromString(value);
      } else {
        std::cerr << "TextParser: I somehow got markup of subtype (" + subtype + ") but it's unsupported for type (" + type.first + ")." << std::endl;  
        return false;
      }
      return true;
    } else if (type.first == "choice")
    {
      // Check if this is a self-contained tag or not
      if (subtype == "val")
      {
        //std::cout << "val" << std::endl;
        addValueChoice(segments, value, activeMarkup);
      } else if (subtype == "branch")
      {
        //std::cout << "branch" << std::endl;
        addBranchChoice(segments, value, activeMarkup);
      } else {
        std::cerr << "TextParser: I somehow got markup of subtype (" + subtype + ") but it's unsupported for type (" + type.first + ")." << std::endl;  
        return false;
      }
      return true;
    } else if (type.first == "text")
    {
      if (subtype == "option")
      {
        addOptionalText(segments, value, activeMarkup);
      } else if (subtype == "variant")
      {
        addVariantText(segments, value, activeMarkup);
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

void TextParser::addValueChoice(std::deque<Utils::SegChoice>& segments, std::string& value, Markup& activeMarkup)
{
  std::vector<Choice> choiceVec;

  // Split on /
  std::stringstream stream(value);
  std::string segment;
  while (std::getline(stream, segment, '/'))
  {
    Choice choice;
    // Split on -
    std::stringstream cStream;
    cStream << segment;
    // Should have exactly two things to look at
    std::string choiceText;
    std::getline(cStream, choiceText, '-');
    choice.text = TextSegment(GlobalSettings::DEFAULTFONT, choiceText, GlobalSettings::DEFAULTTEXTSPEED, activeMarkup);
    std::getline(cStream, choiceText, '-');
    choice.id = choiceText;
    // If there is a third, then this is optional
    choiceText.clear();
    std::getline(cStream, choiceText, '-');
    choice.prereq = choiceText;

    choiceVec.push_back(choice);
  }

  if (choiceVec.size() == 0)
  {
    throw std::runtime_error("TextParser: Didn't find any choices in choice markup! Def: " + value);
  } else {
    sf::Vector2f pos(0.f, 0.f);
    std::unique_ptr<ChoiceBox> cB(new ChoiceBox(choiceVec, pos, activeMarkup, ChoiceType::VALUE));
    segments.push_back(Utils::SegChoice());
    segments.back().choice = std::move(cB);
  }
}

void TextParser::addBranchChoice(std::deque<Utils::SegChoice>& segments,
                                std::string& value,
                                Markup& activeMarkup)
{
  std::vector<Choice> choiceVec;

  // Split on /
  std::stringstream stream(value);
  std::string segment;
  while (std::getline(stream, segment, '/'))
  {
    Choice choice;
    // Split on -
    std::stringstream cStream;
    cStream << segment;
    // Should have exactly two things to look at
    std::string choiceText;
    std::getline(cStream, choiceText, '-');
    choice.text = TextSegment(GlobalSettings::DEFAULTFONT, choiceText, GlobalSettings::DEFAULTTEXTSPEED, activeMarkup);
    std::getline(cStream, choiceText, '-');
    choice.id = choiceText;
    // If there is a third, then this is optional
    choiceText.clear();
    std::getline(cStream, choiceText, '-');
    choice.prereq = choiceText;

    choiceVec.push_back(choice);
  }

  if (choiceVec.size() == 0)
  {
    throw std::runtime_error("TextParser: Didn't find any choices in choice markup! Def: " + value);
  } else {
    sf::Vector2f pos(0.f, 0.f);
    std::unique_ptr<ChoiceBox> cB(new ChoiceBox(choiceVec, pos, activeMarkup, ChoiceType::BRANCH));
    segments.push_back(Utils::SegChoice());
    segments.back().choice = std::move(cB);
  }
}

void TextParser::addOptionalText(std::deque<Utils::SegChoice>& segments,
                                std::string& value,
                                Markup& activeMarkup)
{
  std::vector<std::pair<std::string, std::string> > alternatives;
  std::pair<std::string, std::string> alternative;
  // Split on -
  std::stringstream cStream(value);
  // Should have exactly two things to look at
  std::string text;
  std::getline(cStream, text, '-');
  alternative.first = text;
  text.clear();
  std::getline(cStream, text, '-');
  if (text == "")
  {
    std::cout << "Warning! Text option seems misformed, unlikely to be used: " << value << std::endl;
  }
  alternative.second = text;
  alternatives.push_back(alternative);
  std::unique_ptr<TextSegment> option(new TextSegment(GlobalSettings::DEFAULTFONT, "", GlobalSettings::DEFAULTTEXTSPEED, activeMarkup, alternatives));

  segments.push_back(Utils::SegChoice());
  segments.back().text = std::move(option);
}

void TextParser::addVariantText(std::deque<Utils::SegChoice>& segments,
                                std::string& value,
                                Markup& activeMarkup)
{
  std::vector<std::pair<std::string, std::string> > alternatives;
  std::string defaultString;
  // Split on /
  std::stringstream stream(value);
  std::string segment;
  while (std::getline(stream, segment, '/'))
  {
    std::pair<std::string, std::string> alternative;
    // Split on -
    std::stringstream cStream;
    cStream << segment;
    // Should have exactly two things to look at
    std::string text;
    std::getline(cStream, text, '-');
    alternative.first = text;
    text.clear();
    std::getline(cStream, text, '-');
    alternative.second = text;
    if (alternative.second != "")
    {
      alternatives.push_back(alternative);
    } else {
      defaultString = alternative.first;
    }
  }

  //std::cout << "Adding variant with default: " << defaultString << std::endl;
  std::unique_ptr<TextSegment> tS(new TextSegment(GlobalSettings::DEFAULTFONT, defaultString, GlobalSettings::DEFAULTTEXTSPEED, activeMarkup, alternatives));
  
  segments.push_back(Utils::SegChoice());
  segments.back().text = std::move(tS);
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
  // A tag demonstrating a double
  tag = {"test2", {{"val"}, "double"}};
  validMarkup.insert(tag);
  // A standard choice
  // val = store a value and potentially change shown text
  // branch = a branching choice.
  tag = {"choice", {{"val", "branch"}, "string"}};
  validMarkup.insert(tag);
  // Change something with the font
  // colour = change the colour of the font. Both fill and outline. The format should be 4 numbers corresponding to the Uint8 values for RGBA (red, green, blue, alpha (opacity)) - in that order.
  // TODO support the SFML presets.
  tag = {"font", {{"colour"}, "string"}};
  validMarkup.insert(tag);
  // Do something with text
  // option = optional text depending on previous choices.
  // variant = text which varies depending on previous choices.
  tag = {"text", {{"option", "variant"}, "string"}};
  validMarkup.insert(tag);
  // A tag to be ignored
  tag = {"ignore", {{""}, ""}};
  // For some reason I can't leave that empty in a statin method according to g++4.9 so we create it with something and then clear it
  tag.second.first.clear();
  validMarkup.insert(tag);
  return validMarkup;
}

sf::Color TextParser::getColourFromString(std::string& rgbaString)
{
  // There should be four values
  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;
  uint8_t alpha = 0;

  // We assume there is four comma seperated values and will warn if not.
  size_t pos = 0;
  pos = rgbaString.find(',');
  try
  {
    red = std::stoul(rgbaString.substr(0, pos));
  } catch (...) {
    std::cerr << "Warning! Couldn't identify red in rgbaString. Setting to 0." << std::endl;
    red = 0;
  }
  rgbaString = rgbaString.substr(pos+1);
  pos = rgbaString.find(',');
  try
  {
    green = std::stoul(rgbaString.substr(0, pos));
  } catch (...) {
    std::cerr << "Warning! Couldn't identify green in rgbaString. Setting to 0." << std::endl;
    green = 0;
  }
  rgbaString = rgbaString.substr(pos+1);
  pos = rgbaString.find(',');
  try
  {
    blue = std::stoul(rgbaString.substr(0, pos));
  } catch (...) {
    std::cerr << "Warning! Couldn't identify blue in rgbaString. Setting to 0." << std::endl;
    blue = 0;
  }
  rgbaString = rgbaString.substr(pos+1);
  pos = rgbaString.find(',');
  try
  {
    alpha = std::stoul(rgbaString.substr(0, pos));
  } catch (...) {
    std::cerr << "Warning! Couldn't identify alpha in rgbaString. Setting to 0." << std::endl;
    alpha = 0;
  }

  return sf::Color(red, green, blue, alpha);
}

std::string TextParser::getColourStringFromSFColor(sf::Color& colour)
{
  std::string rgbaString;
  rgbaString += std::to_string(colour.r);
  rgbaString += ",";
  rgbaString += std::to_string(colour.g);
  rgbaString += ",";
  rgbaString += std::to_string(colour.b);
  rgbaString += ",";
  rgbaString += std::to_string(colour.a);
  return rgbaString;
}

} // End namespace StoryTime