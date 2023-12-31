
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

include(CTest)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    add_subdirectory(tests)
endif ()

enable_testing()
