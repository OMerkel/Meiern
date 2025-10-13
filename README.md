# Meiern

## Usage

### Install on Linux

In case your Linux is supported by apt package manager:

``` bash
.../meiern$ sudo apt-get update
.../meiern$ sudo apt-get upgrade
.../meiern$ sudo apt-get install build-essential
.../meiern$ sudo apt install cmake libgtest-dev gdb
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
gcovr -r . --object-directory build/
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
