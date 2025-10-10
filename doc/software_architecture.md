
# Meiern Software Architecture

**Version:** 1.0.1
**Author:** OMerkel
**Last Update:** October 10, 2025

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

- **Player**
  - Represents a player in the game.
  - Attributes:
    - `name`: Player name
    - `lives`: Number of lives
    - `MeiernDiceCup*`: Optional dice cup
  - Methods:
    - `increaseLives()`
    - `decreaseLives()`
    - `announceValue()`
    - `trustPreviousAnnouncement()`
    - `doubtPreviousAnnouncement()`
    - `performTurn()`

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
Player               Die
  |                   ♢ *
  |                   |
  ♢ 0,1               |                   
MeiernDiceCup <--- DiceCup

```

**Legend:**

- `<---` means "inherits from" (Inheritance)
- `♢---` means "aggregates" (Aggragation)
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
  Player alice("Alice", 3);
  MeiernDiceCup cup;
  alice.setDiceCup(&cup);
  ```

<!-- markdownlint-disable-next-line MD029 -->
2. Alice rolls and announces:

  ```cpp
  Announcement announcement =  alice.performTurn();
  ```

<!-- markdownlint-disable-next-line MD029 -->
3. Bob compares with his own roll:

  ```cpp
  Announcement bobAnnouncement(5, 2);
  if (bobAnnouncement < previousAnnouncement) {
     // Bob's roll is lower
  }
  ```

<!-- markdownlint-disable-next-line MD029 -->
4. Game continues until one player is remaining.

---

## Test Coverage

- All core classes have dedicated unit tests in `gtest/`:
  - CyclicList, Die, DiceCup, MeiernDiceCup, Announcement, Player, Game
- Tests cover normal, edge, and error cases for all major methods.
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

---

## Example Usage

```cpp
// Create a player and dice cup
Player player("Alice", 3);
MeiernDiceCup cup;
player.setDiceCup(&cup);

// Player performs a turn
int announcedValue = player.performTurn();

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

- `src/` — Core source files
- `gtest/` — Unit tests
- `doc/` — Documentation
- `bin/` — Compiled binaries
- `CMakeLists.txt`, `Makefile` — Build configuration

---

## Summary

Meiern’s architecture is modular, testable, and extensible, with clear separation of game logic, data representation, and player interaction. Each class encapsulates a distinct concept, and the use of modern C++ features ensures maintainability and reliability.
