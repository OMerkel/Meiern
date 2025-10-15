# Meiern

## Usage

### Install on Linux

In case your Linux is supported by apt package manager:

``` bash
.../meiern$ sudo apt-get update
.../meiern$ sudo apt-get upgrade
.../meiern$ sudo apt-get install build-essential
.../meiern$ sudo apt install cmake libgtest-dev gdb ninja-build
.../meiern$ sudo apt install gcovr
```

### Build and Run

``` bash
.../meiern$ cmake .
.../meiern$ cmake --build . -v
```

Enforcing a specific compiler (here clang++ / clang).

``` bash
.../meiern$ cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_C_COMPILER=/usr/bin/clang .
```

To explicitely build with debug symbols:

``` bash
.../meiern$ cmake -DCMAKE_BUILD_TYPE=Debug 
```

To explicitely build release type:

``` bash
.../meiern$ cmake -DCMAKE_BUILD_TYPE=Release 
```

Even more sophisticated alternative:

``` bash
.../meiern$ /usr/bin/cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ --no-warn-unused-cli -S ~/github/Meiern -B ~/github/Meiern/build -G Ninja
.../meiern$ /usr/bin/cmake --build ~/github/Meiern/build --config Debug --target all --
```

To run tests and then run the binary:

``` bash
.../meiern$ bin/meiern_tests # to run the tests
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
.../meiern$ bin/meiern
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
.../meiern$ gcovr -r . --object-directory build/
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
