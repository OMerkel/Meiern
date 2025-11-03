cmake_minimum_required(VERSION 3.14)

# Doxygen support
# find_package(Doxygen QUIET)
find_package(Doxygen REQUIRED)

if(DOXYGEN_FOUND)
    set(DOXYFILE_IN ${CMAKE_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYFILE_OUT ${CMAKE_BINARY_DIR}/Doxyfile)
    set(PROJECT_NAME "Meiern")
    set(PROJECT_VERSION "1.0.4")
    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docs
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()

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

# Add include directory for headers
include_directories(${CMAKE_SOURCE_DIR}/include)

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
)

target_compile_options(meiern PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Werror -Wconversion -Wshadow>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
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
