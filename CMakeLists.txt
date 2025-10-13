cmake_minimum_required(VERSION 3.14)
project(meiern LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Coverage flags for GCC/Clang
option(COVERAGE "Enable coverage reporting" ON)
if(COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(--coverage -g -O0)
        add_link_options(--coverage)
    endif()
endif()

add_executable(meiern
    src/meiern_main.cpp
    src/Announcement.cpp
    src/DiceCup.cpp
    src/Die.cpp
    src/Game.cpp
    src/Greeting.cpp
    src/Interaction.cpp
    src/Logger.cpp
    src/MeiernDiceCup.cpp
    src/Player.cpp
)

# Set output directory for binaries
set_target_properties(meiern PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)


enable_testing()
add_subdirectory(gtest)

# Add test for gtest target if it exists
if(TARGET meiern_tests)
    add_test(NAME meiern_tests COMMAND meiern_tests)
endif()

# Add gcovr coverage target
find_program(GCOVR_PATH gcovr)
if(GCOVR_PATH)
    add_custom_target(coverage
        COMMAND ${GCOVR_PATH} -r ${CMAKE_SOURCE_DIR} --html --html-details -o coverage.html
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating coverage report with gcovr"
    )
endif()
