#include "GameSlice.hpp"

namespace StoryTime {

GameSlice::GameSlice() :
  _needsDraw(false)
{
  // Do nothing
}

bool GameSlice::needsDraw() { return _needsDraw; }

void GameSlice::redraw() { _needsDraw = true; }

void GameSlice::drawComplete() { _needsDraw = false; }

} // End namespace StoryTime

