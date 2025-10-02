# Meiern Software Architecture

## Overview

Meiern is a C++ implementation of the classic dice game "Meiern" (Mäxchen). The software is modular, test-driven, and designed for extensibility and clarity. The architecture is object-oriented, with each game concept represented by a dedicated class.

---

## Main Components

### 1. Core Game Classes

- **Die** Represents a single die. Supports custom number of sides and random rolling.  
  - Attributes: `sides`, `value`  
  - Methods: `roll()`, `getValue()`

- **DiceCup** Aggregates multiple dice. Supports shaking (rolling all dice), adding/removing dice, and accessing individual dice.  
  - Attributes: `std::vector<std::unique_ptr<Die>> dice`  
  - Methods: `shake()`, `addDie()`, `removeDie()`, `getDiceCount()`, `getDie()`

- **MeiernDiceCup** Inherits from `DiceCup`. Always contains exactly two six-sided dice, as required by Meiern rules.

- **Announcement** Encodes and compares the value of a dice announcement according to Meiern rules.  
  - Attributes: `encodedValue`, `value`  
  - Methods: Comparison operators, `getValue()`, `getEncodedValue()`

- **AnnouncementVector** Container for a sequence of `Announcement` objects. Supports vector-like operations and lexicographical comparison.

- **Player** Represents a player in the game.  
  - Attributes: `name`, `lives`, optional `MeiernDiceCup*`  
  - Methods: `increaseLives()`, `decreaseLives()`, `announceValue()`, `trustPreviousAnnouncement()`, `doubtPreviousAnnouncement()`, `performTurn()`

---

### 2. Game Logic

- **Game Flow** Players take turns rolling dice, making announcements, and challenging previous announcements. The game logic is implemented in the main application and/or dedicated game manager classes.

- **Announcement Encoding** The rules for ranking dice combinations (Meier, doubles, normal combinations) are encoded in the `Announcement` class, allowing for direct comparison and validation.

---

### 3. Testing

- **Unit Tests** All core classes are covered by Google Test-based unit tests, located in the `gtest/` directory.  
  - `test_die.cpp`, `test_dicecup.cpp`, `test_meierndicecup.cpp`, `test_announcement.cpp`, etc.

---

### 4. Build System

- **CMake** The project uses CMake for cross-platform builds. All source and test files are included in the build configuration.

---

## Extensibility

- New game rules or variants can be added by extending the core classes.
- Additional player actions or game states can be implemented with minimal changes to the architecture.

---

## Dependencies

- **Standard C++ Library** For containers, algorithms, and random number generation.
- **Google Test** For unit testing.

---

## Directory Structure

- `src/` — Core source files
- `gtest/` — Unit tests
- `doc/` — Documentation
- `bin/` — Compiled binaries
- `CMakeLists.txt`, `Makefile` — Build configuration

---

## Summary

Meiern’s architecture is modular, testable, and extensible, with clear separation of game logic, data representation, and player interaction. Each class encapsulates a distinct concept, and the use of modern C++ features ensures maintainability and reliability.
