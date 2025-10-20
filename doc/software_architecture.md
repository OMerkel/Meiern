# Meiern Software Architecture

**Version:** 1.0.4
**Author:** OMerkel
**Last Update:** October 18, 2025

---

## Overview

Meiern is a C++ implementation of the classic dice game "Meiern" (Mäxchen). The software is modular, test-driven, and designed for extensibility and clarity. The architecture is object-oriented, with each game concept represented by a dedicated class.

---

## Main Components

### 1. Core Game Classes

- **Die**
  - Represents a single die. Supports custom number of sides and random rolling.
  - Attributes:
    - `sides`: Number of sides
    - `value`: Current value
  - Methods:
    - `roll()`
    - `getValue()`

- **DiceCup**
  - Aggregates multiple dice. Supports shaking (rolling all dice), adding/removing dice, and accessing individual dice.
  - Attributes:
    - `std::vector<std::unique_ptr<Die>> dice`
  - Methods:
    - `shake()`
    - `addDie()`
    - `removeDie()`
    - `getDiceCount()`
    - `getDie()`

- **MeiernDiceCup**
  - Inherits from `DiceCup`. Always contains exactly two six-sided dice, as required by Meiern rules.

- **Announcement**
  - Encodes and compares the value of a dice announcement according to Meiern rules.
  - Attributes:
    - `encodedValue`: Ranking value for comparison
    - `value`: Raw dice value
  - Methods:
    - Comparison operators
    - `getValue()`
    - `getEncodedValue()`

- **AbstractPlayer**
  - Abstract base class for all player types. Defines the interface for player actions and state.
  - Subclasses:
    - [`HumanPlayer`](include/HumanPlayer.h): Implements interactive console input/output.
    - [`AIPlayerSimple`](include/AIPlayerSimple.h): Implements a simple AI strategy.
  - Attributes:
    - `name`: Player name
    - `lives`: Number of lives
    - `MeiernDiceCup* diceCup`: Optional dice cup
  - Methods (all virtual):
    - `getName()`, `getLives()`, `getLivesAsString()`
    - `increaseLives()`, `decreaseLives()`
    - `setDiceCup()`, `getDiceCup()`
    - `performTurn()` (pure virtual)
    - `announceValue()` (pure virtual)
    - `trustPreviousAnnouncement()` (pure virtual)
    - `doubtPreviousAnnouncement()` (pure virtual)

- **AIPlayerSimple**
  - Inherits from `AbstractPlayer`. Implements a simple AI strategy for all required virtual methods.
  - Used as the default AI player in the game.

- **HumanPlayer**
  - Inherits from `AbstractPlayer`. Implements all required virtual methods with interactive console input/output.
  - Used for human-controlled players.

- **Logger**
  - Provides thread-safe, singleton-based logging to console and/or file.
  - Attributes:
    - `static std::ofstream file_`: Shared log file stream
    - `bool consoleEnabled_`, `bool fileEnabled_`: Sink control
    - `std::atomic<Level> consoleLevel_`, `fileLevel_`: Per-sink log levels
  - Methods:
    - `Logger::instance()`: Singleton accessor
    - `enableConsole(bool)`, `enableFile(bool)`: Enable/disable sinks
    - `setLogFile(path, append)`: Set log file
    - `setConsoleLevel(Level)`, `setFileLevel(Level)`, `setAllLevels(Level)`: Log level control
    - `trace()`, `debug()`, `info()`, `warn()`, `error()`, `critical()`: Stream-style logging
    - RAII `LogStream` proxy for safe, move-only log emission
  - Design:
    - Private constructor, deleted copy/move semantics
    - All logging uses `Logger::instance()`
    - Logging is disabled if no sink is enabled
    - File and console output can be independently controlled
    - Fully covered by dedicated unit tests

---

### 1.1 Class Relationships (UML Diagram)

``` uml
Announcement
  ♢ 1
  |
  | 1
Game
  | 1
  |
  ◆ 1
CyclicList
  |
  |
  ♢ 1..*
AbstractPlayer <--- HumanPlayer
               <--- AIPlayerSimple
  |
  |
  |                  Die
  |                   ♢ *
  ♢ 0,1               |
MeiernDiceCup <--- DiceCup

```

**Legend:**

- `<---` means "inherits from" (Inheritance)
- `♢---` means "aggregates" (Aggregation)
- `◆---` means "composes" (Composition)

As an optional information each relations arrow end might show a multiplicity if applicable.

---

## Error Handling

- Invalid dice values or announcements are handled by setting indices to `-1` and returning default/empty objects.
- Methods like `nextHigher()` and `allHigher()` return invalid or empty results if called on the highest or invalid announcement.

---

## Thread Safety

- The code is **not thread-safe** by default. Shared static containers (e.g., in `Announcement`) are not protected against concurrent access.
- For multi-threaded use, mutexes or thread-local storage should be added.

---

## Performance Considerations

- Dice rolling uses a single RNG per die or a static RNG for all dice, minimizing overhead.
- Announcement lookup uses a static vector for fast index-based access.

---

## Example Game Session


1. Create players and assign dice cups:

  ```cpp
  std::unique_ptr<AbstractPlayer> alice = std::make_unique<HumanPlayer>("Alice", 3);
  std::unique_ptr<MeiernDiceCup> cup = std::make_unique<MeiernDiceCup>();
  alice->setDiceCup(cup.get());
  ```

<!-- markdownlint-disable-next-line MD029 -->
2. Alice rolls and announces:

  ```cpp
  Announcement announcement = alice->performTurn(previousAnnouncement);
  ```

<!-- markdownlint-disable-next-line MD029 -->
3. Bob (AI) compares with his own roll:

  ```cpp
  std::unique_ptr<AbstractPlayer> bob = std::make_unique<AIPlayerSimple>("Bob", 3);
  Announcement bobAnnouncement(5, 2);
  if (bobAnnouncement < previousAnnouncement) {
     // Bob's roll is lower
  }
  ```

<!-- markdownlint-disable-next-line MD029 -->
4. Game continues until one player is remaining.

---

## Test Coverage

- All core classes, including AI and Human players, are covered by Google Test-based unit tests in [`gtest/`](gtest).
  - CyclicList, Die, DiceCup, MeiernDiceCup, Announcement, Player, Game, Logger
- Logger tests cover:
  - Console and file sink enable/disable
  - Log file setup, invalid file handling
  - All log levels and stream entry points
  - RAII and move semantics for `LogStream`
  - Disabled logging (no sink enabled)
  - Manipulators and flush
- All lines in Logger are covered, including error and edge cases.
- To run tests:
  - Build with CMake
  - Run the test executable in `bin/`

---

## Future Work / TODOs

- Add support for custom game variants and rules.
- Improve thread safety for concurrent games.
- Add graphical user interface (GUI) or web frontend.
- Refactor static containers for better encapsulation.
- Expand documentation with more diagrams and examples.

---

---

## Game Logic

- **Game Flow**
  1. Each player takes a turn.
  2. The player rolls the dice (using their `MeiernDiceCup`).
  3. The player announces a value (using the `Announcement` class) higher than previous announcement.
  4. The next player may trust or doubt the new announcement.
  5. If doubted, the actual dice are revealed and the outcome is resolved.
  6. Lives are adjusted accordingly.

- **Announcement Encoding**
  - The rules for ranking dice combinations (Meier, doubles, normal combinations) are encoded in the `Announcement` class, allowing for direct comparison and validation.

- **Ranking order (lowest to highest)**
  - Normal: 31, 32, 41, 42, 43, 51, 52, 53, 54, 61, 62, 63, 64, 65
  - Doubles: 11, 22, 33, 44, 55, 66
  - Meier: 21

Each normal value can be rolled in 2 ways, each double in 1 way, Meier in 2 ways.

Total possible rolls: 36

| Announcement | # Lower or Equal | Probability      |
|--------------|------------------|------------------|
| 31           | 2                | 2/36 ≈ 5.56%     |
| 32           | 4                | 4/36 ≈ 11.11%    |
| 41           | 6                | 6/36 ≈ 16.67%    |
| 42           | 8                | 8/36 ≈ 22.22%    |
| 43           | 10               | 10/36 ≈ 27.78%   |
| 51           | 12               | 12/36 ≈ 33.33%   |
| 52           | 14               | 14/36 ≈ 38.89%   |
| 53           | 16               | 16/36 ≈ 44.44%   |
| 54           | 18               | 18/36 = 50.00%   |
| 61           | 20               | 20/36 ≈ 55.56%   |
| 62           | 22               | 22/36 ≈ 61.11%   |
| 63           | 24               | 24/36 ≈ 66.67%   |
| 64           | 26               | 26/36 ≈ 72.22%   |
| 65           | 28               | 28/36 ≈ 77.78%   |
| 11           | 29               | 29/36 ≈ 80.56%   |
| 22           | 30               | 30/36 ≈ 83.33%   |
| 33           | 31               | 31/36 ≈ 86.11%   |
| 44           | 32               | 32/36 ≈ 88.89%   |
| 55           | 33               | 33/36 ≈ 91.67%   |
| 66           | 34               | 34/36 ≈ 94.44%   |
| 21 (Meier)   | 36               | 36/36 = 100%     |

---

## Example Usage

```cpp

// Create a human player and dice cup
std::unique_ptr<AbstractPlayer> player = std::make_unique<HumanPlayer>("Alice", 3);
std::unique_ptr<MeiernDiceCup> cup = std::make_unique<MeiernDiceCup>();
player->setDiceCup(cup.get());

// Player performs a turn
int announcedValue = player->performTurn(previousAnnouncement);

// Compare announcements
Announcement a1(6, 6); // Double six
Announcement a2(1, 2); // Meier
if (a2 > a1) {
    // Meier outranks double six
}
```

---

## Testing

- **Unit Tests**
  - All core classes are covered by Google Test-based unit tests, located in the `gtest/` directory.
    - `test_die.cpp`, `test_dicecup.cpp`, `test_meierndicecup.cpp`, `test_announcement.cpp`, etc.

---

## Build System

- **CMake**
  - The project uses CMake for cross-platform builds. All source and test files are included in the build configuration.

---

## Extensibility

- New game rules or variants can be added by extending the core classes (e.g., subclassing `DiceCup` or `Announcement`).
- Additional player actions or game states can be implemented with minimal changes to the architecture.

---

## Dependencies

- **Standard C++ Library**
  - For containers, algorithms, and random number generation.
- **Google Test**
  - For unit testing.

---

## Directory Structure

- `src/` — Core source files (implementation)
- `include/` — Header files for all classes
- `gtest/` — Unit tests
- `doc/` — Documentation
- `bin/` — Compiled binaries
- `CMakeLists.txt`, `Makefile` — Build configuration

---

## Summary

Meiern’s architecture is modular, testable, and extensible, with clear separation of game logic, data representation, and player interaction. Each class encapsulates a distinct concept, and the use of modern C++ features ensures maintainability and reliability.
