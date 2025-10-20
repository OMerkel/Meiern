cmake_minimum_required(VERSION 3.14)
project(meiern_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")

# GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(
    meiern_tests
    test_aiplayersimple.cpp
    test_announcement.cpp
    test_cycliclist.cpp
    test_dicecup.cpp
    test_die.cpp
    test_game.cpp
    test_greeting.cpp
    test_interaction.cpp
    test_meierndicecup.cpp
    test_logger.cpp
    ../src/Announcement.cpp
    ../src/DiceCup.cpp
    ../src/Die.cpp
    ../src/Game.cpp
    ../src/Greeting.cpp
    ../src/Interaction.cpp
    ../src/Logger.cpp
    ../src/MeiernDiceCup.cpp
)

target_include_directories(meiern_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(meiern_tests PRIVATE GTest::gtest_main)

# Set output directory for binaries
set_target_properties(meiern_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

include(GoogleTest)
gtest_discover_tests(meiern_tests)
