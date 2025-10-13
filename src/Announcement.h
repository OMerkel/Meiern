#pragma once
#include <algorithm>
#include <vector>

/**
 * @class Announcement
 * @brief Represents a player's announcement in the game.
 */
class Announcement {
private:
    int index;
    static std::vector<int> announcements;

public:
    Announcement(int die1, int die2) {
        if(announcements.empty()) {
            announcements.clear();
            announcements.reserve(21); // Reserve space for 21 announcements
            announcements.push_back(31); // Initial announcement
            announcements.push_back(32);
            announcements.push_back(41);
            announcements.push_back(42);
            announcements.push_back(43);
            announcements.push_back(51);
            announcements.push_back(52);
            announcements.push_back(53);
            announcements.push_back(54);
            announcements.push_back(61);
            announcements.push_back(62);
            announcements.push_back(63);
            announcements.push_back(64);
            announcements.push_back(65);
            announcements.push_back(11); // Doubles start here
            announcements.push_back(22);
            announcements.push_back(33);
            announcements.push_back(44);
            announcements.push_back(55);
            announcements.push_back(66);
            announcements.push_back(21); // Meier is highest
        }
        int high = std::max(die1, die2);
        int low = std::min(die1, die2);
        int value = high * 10 + low;
        for (size_t i = 0; i < announcements.size(); ++i) {
            if (announcements[i] == value) {
                index = static_cast<int>(i);
                return;
            }
        }
        index = -1; // Invalid announcement
    }

    // Returns the next higher Announcement, or an invalid Announcement if at the highest
    Announcement nextHigher() const {
        if (index < 0 || index + 1 >= static_cast<int>(announcements.size())) {
            return Announcement(0, 0); // Invalid
        }
        int nextValue = announcements[index + 1];
        int die1 = nextValue / 10;
        int die2 = nextValue % 10;
        return Announcement(die1, die2);
    }

    // Returns a vector of all higher Announcements than the current one
    std::vector<Announcement> allHigher() const {
        std::vector<Announcement> result;
        if (index < 0 || index + 1 >= static_cast<int>(announcements.size())) {
            return result;
        }
        for (int i = index + 1; i < static_cast<int>(announcements.size()); ++i) {
            int value = announcements[i];
            int die1 = value / 10;
            int die2 = value % 10;
            result.emplace_back(die1, die2);
        }
        return result;}

    const int& operator[](size_t idx) const {
        return announcements.at(idx);
    }

    void clear() {
        announcements.clear();
    }

    bool operator<(const Announcement& other) const { return index < other.index; }
    bool operator<=(const Announcement& other) const { return index <= other.index; }
    bool operator>(const Announcement& other) const { return index > other.index; }
    bool operator>=(const Announcement& other) const { return index >= other.index; }
    bool operator==(const Announcement& other) const { return index == other.index; }
    bool operator!=(const Announcement& other) const { return index != other.index; }
    int getValue() const {
        return index >= 0 && index < static_cast<int>(announcements.size()) ?
        announcements[index] : 0;
    }
    int getEncodedValue() const { return index; }

};
