# Meiern

Meiern is a C++ implementation of the classic dice game "Meiern" (Mäxchen). The software is modular, test-driven, and designed for extensibility and clarity. The architecture is object-oriented, with each game concept represented by a dedicated class.

## Usage

### Build Environment Install on...

This section is to support with FAQ that might come up depending on your selected OS.
For Unix-alike OS see [pkgs.org](https://pkgs.org/) on any package information.

#### ... Linux

In case your Linux is supported by apt package manager:

``` bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install build-essential
sudo apt install cmake libgtest-dev gdb ninja-build
sudo apt install gcovr
sudo apt install doxygen graphviz
```

#### ... MacOS

If you like to use [Homebrew](https://brew.sh/)

``` zsh
brew install llvm
brew install cmake
brew install googletest
brew install ninja
brew install gdb
brew install gcovr
```

If you prefer to use [MacPorts](https://ports.macports.org/)

``` zsh
sudo port install clang-20
sudo port install cmake
sudo port install gtest
sudo port install ninja
sudo port install gdb
sudo port install gcovr
```

#### ... FreeBSD, OpenBSD, GhostBSD

Some BSD do not come with dev tools installed, e.g. GhostBSD.
Meaning that for instance standard system includes might be missing. In such a case follow the hints on
[GhostBSD Documentation Portal](https://ghostbsd-documentation-portal.readthedocs.io/en/latest/user/FAQ.html#why-can-t-i-compile-code-or-ports-on-ghostbsd)

``` bash
sudo pkg install -g 'GhostBSD*-dev'
```

In general on FreeBSD

``` bash
sudo pkg update
sudo pkg upgrade
sudo pkg install git
sudo pkg install llvm  # usually already installed, but to be explicit
sudo pkg install cmake
sudo pkg install gmake  # usually already installed
sudo pkg install ninja
sudo pkg install gdb
sudo pkg install googletest
```

### Build and Run

``` bash
cmake --version
cmake .
cmake --build . -v
```

Enforcing a specific compiler (here clang++ / clang).

``` bash
cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_C_COMPILER=/usr/bin/clang .
```

To explicitely build with debug symbols:

``` bash
cmake -DCMAKE_BUILD_TYPE=Debug 
```

To explicitely build release type:

``` bash
cmake -DCMAKE_BUILD_TYPE=Release 
```

Even more sophisticated alternative:

``` bash
/usr/bin/cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ --no-warn-unused-cli -S ~/github/Meiern -B ~/github/Meiern/build -G Ninja
/usr/bin/cmake --build ~/github/Meiern/build --config Debug --target all --
```

To run tests and then run the binary:

``` bash
bin/meiern_tests # to run the tests

Running main() from ./googletest/src/gtest_main.cc
[==========] Running 8 tests from 3 test suites.
[----------] Global test environment set-up.
[----------] 5 tests from CyclicListTest
[ RUN      ] CyclicListTest.PushBackAndSize
[       OK ] CyclicListTest.PushBackAndSize (0 ms)
[ RUN      ] CyclicListTest.CyclicNext
[       OK ] CyclicListTest.CyclicNext (0 ms)
[ RUN      ] CyclicListTest.CyclicPrev
[       OK ] CyclicListTest.CyclicPrev (0 ms)
[ RUN      ] CyclicListTest.EmptyList
[       OK ] CyclicListTest.EmptyList (0 ms)
[ RUN      ] CyclicListTest.StringType
[       OK ] CyclicListTest.StringType (0 ms)
[----------] 5 tests from CyclicListTest (0 ms total)

[----------] 2 tests from GreetingTest
[ RUN      ] GreetingTest.ReturnsCorrectGreeting
[       OK ] GreetingTest.ReturnsCorrectGreeting (0 ms)
[ RUN      ] GreetingTest.EmptyName
[       OK ] GreetingTest.EmptyName (0 ms)
[----------] 2 tests from GreetingTest (0 ms total)

[----------] 1 test from InteractionTest
[ RUN      ] InteractionTest.OutputPrintsMessage
[       OK ] InteractionTest.OutputPrintsMessage (0 ms)
[----------] 1 test from InteractionTest (0 ms total)

[----------] Global test environment tear-down
[==========] 8 tests from 3 test suites ran. (0 ms total)
[  PASSED  ] 8 tests.

bin/meiern  # to start the game
```

Alternatively use ctest

``` bash
ctest --test-dir build --output-on-failure
```

For code coverage measurement CMakeLists.txt has to include some build flags to be set.

``` bash
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")
```

After clean building and running the tests the coverage tooling must execute

``` bash
gcovr -r . --object-directory build/

(WARNING) relative referencing in --object-directory.
        this could cause strange errors when gcovr attempts to
        identify the original gcc working directory.
------------------------------------------------------------------------------
                           GCC Code Coverage Report
Directory: .
------------------------------------------------------------------------------
File                                       Lines    Exec  Cover   Missing
------------------------------------------------------------------------------
gtest/test_announcement.cpp                  156     156   100%   
gtest/test_cycliclist.cpp                     52      52   100%   
gtest/test_dicecup.cpp                        45      45   100%   
gtest/test_die.cpp                            23      23   100%   
gtest/test_game.cpp                           38      38   100%   
gtest/test_greeting.cpp                        8       8   100%   
gtest/test_interaction.cpp                    11      11   100%   
gtest/test_logger.cpp                        205     205   100%   
gtest/test_meierndicecup.cpp                  21      21   100%   
gtest/test_player.cpp                         77      77   100%   
src/Announcement.h                            65      65   100%   
src/CyclicList.h                              14      14   100%   
src/DiceCup.cpp                               21      21   100%   
src/Die.cpp                                    9       9   100%   
src/Game.cpp                                 114     110    96%   88,107-109
src/Greeting.cpp                               3       3   100%   
src/Interaction.cpp                            5       5   100%   
src/Logger.cpp                                34      34   100%   
src/Logger.h                                  60      60   100%   
src/MeiernDiceCup.cpp                          9       9   100%   
src/MeiernDiceCup.h                            1       1   100%   
src/Player.cpp                                64      64   100%   
src/meiern_main.cpp                            6       6   100%   
------------------------------------------------------------------------------
TOTAL                                       1041    1037    99%
------------------------------------------------------------------------------
```

Generating the report in HTML format:

``` bash
gcovr -r . --object-directory build/ --html --html-details -o coverage.html
```

### Debug in VSCode / WSL

In launch.json set "miDebuggerPath" and "cwd" according to your local path settings.

In case "the value of miDebuggerPath is invalid":

* In case you are using VSCode in Windows and plan to develop and run code in WSL,
  * then make sure you have the "Remote - WSL" extension installed in VS Code
* SHIFT+CTRL P , following depends a bit on your versions but select either
  * "Remote-WSL: New Window" or
  * "Remote-WSL: Reopen Folder in WSL" or
  * "WSL: Connect to WSL" or similar from the menu

### Build Documentation with Doxygen

Use the CMake custom target doc

``` bash
/usr/bin/cmake --build <your-repository-directory>/Meiern/build --config Debug --target doc --
```

\<your-repository-directory\> has to be set to a valid path in your environment

Then the HTML documentation is generated in 'build/html'
