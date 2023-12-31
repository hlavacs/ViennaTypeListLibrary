#project(MyLibTests LANGUAGES CXX)

include(CTest)

set(TARGET testlib)

set(SOURCE testlib.cpp)

set(HEADERS )

add_executable(${TARGET} ${SOURCE} ${HEADERS})

target_compile_features(${TARGET} PUBLIC cxx_std_20)

target_include_directories(${TARGET} PUBLIC ../include)

add_test(NAME ${TARGET} COMMAND testlib) # Command can be a target
