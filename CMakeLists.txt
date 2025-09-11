cmake_minimum_required(VERSION 3.14)
project(meiern LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(meiern
    src/meiern_main.cpp
    src/Game.cpp
    src/Greeting.cpp
    src/Interaction.cpp
    src/Player.cpp
)

# Set output directory for binaries
set_target_properties(meiern PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

add_subdirectory(gtest)
