
cmake_minimum_required (VERSION 3.5.0)
project (
  "ViennaTypeListLibrary"
  VERSION 1.0
  DESCRIPTION "A meta programming library for lists of types."
  LANGUAGES CXX
)

# enforce C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

# enable clang-tidy. disable to speed up compilation
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=readability-*;cppcoreguidelines-*;-header-filter=.*; -p build)


if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
  include(CTest)
  add_subdirectory(tests)
endif ()
