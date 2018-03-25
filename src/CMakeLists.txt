set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${StoryTime_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${StoryTime_BINARY_DIR}/lib)
set(CMAKE_INSTALL_PREFIX ${StoryTime_BINARY_DIR}/build)

# includes
include_directories(${StoryTime_SOURCE_DIR}/include)

# additional library paths
link_directories(${StoryTime_SOURCE_DIR}/lib)

# Source files
set(SOURCE GameSlice.cpp OpeningScreen.cpp MenuScreen.cpp GlobalSettings.cpp MainGame.cpp TextHandler.cpp ChoiceBox.cpp TextSegment.cpp TextParser.cpp StoryVerifier.cpp)

# Executables
add_executable(StoryTime StoryTime.cpp ${SOURCE})

# Libraries groups
set(SFML sfml-audio sfml-graphics sfml-network sfml-system sfml-window)

# Linking
target_link_libraries(StoryTime ${SFML})