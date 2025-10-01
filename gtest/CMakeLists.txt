cmake_minimum_required(VERSION 3.14)
project(meiern_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(
    meiern_tests
    test_cycliclist.cpp
    test_greeting.cpp
    test_interaction.cpp
    test_player.cpp
    ../src/Greeting.cpp
    ../src/Interaction.cpp
    ../src/Player.cpp
)

target_include_directories(meiern_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_link_libraries(meiern_tests PRIVATE GTest::gtest_main)

# Set output directory for binaries
set_target_properties(meiern_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
