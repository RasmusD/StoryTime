cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wconversion -g")

project (StoryTime)
# The version number.
set (StoryTime_VERSION_MAJOR 0)
set (StoryTime_VERSION_MINOR 5)

add_subdirectory(src)
