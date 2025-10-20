/**
 * @file AbstractPlayer.h
 * @brief Declaration of the AbstractPlayer class.
 * 
 * This file contains the definition of the AbstractPlayer class,
 * which serves as a base class for different types of players in the Meiern dice game.
 *
 * The Player class encapsulates the state and behavior of a player, including their name,
 * current number of lives, and interaction with the dice cup. It provides methods for
 * managing lives, performing turns, announcing dice values, and interacting with game
 * announcements.
 *
 * @author Oliver Merkel
 * @date 2025-10-14
 *
 * @note This class relies on the Announcement, Logger, and MeiernDiceCup classes
 *       for game logic and output.
 *
 */
#pragma once
#include <string>
#include "Announcement.h"
#include "Logger.h"
#include "MeiernDiceCup.h"

class AbstractPlayer {
protected:
    std::string name_;
    int lives_;
    MeiernDiceCup* diceCup_ = nullptr;
    Logger& logger_ = Logger::instance();
public:
    AbstractPlayer(const std::string& name, int initialLives)
        : name_(name), lives_(initialLives) {}
    virtual ~AbstractPlayer() = default;

    /**
     * @brief Retrieves the name of the player.
     * @return The player's name as a constant reference to a string.
     */
    const std::string& getName() const { return name_; }
    
    
    /**
     * @brief Retrieves the current number of lives the player has.
     * @return The number of lives as an integer.
     */
    int getLives() const { return lives_; }


    /**
     * @brief Retrieves the player's lives as a formatted string.
     * @return A string representing the number of lives, e.g., "3 lives" or "1 life".
     */
    std::string getLivesAsString() const {
        return std::to_string(lives_) + (lives_ == 1 ? " life" : " lives");
    }


    /**
     * @brief Increases the player's lives by a specified amount.
     * @param amount The number of lives to add (default is 1).
     */
    void increaseLives(int amount = 1) { lives_ += amount; }


    /**
     * @brief Decreases the player's lives by a specified amount.
     * @param amount The number of lives to subtract (default is 1).
     * @return true if the player is still alive (lives > 0),
     *         false if the player has no lives left.
     */
    virtual bool decreaseLives(int amount = 1) {
        logger_.info() << "[" << name_ << "] " << "gets lives reduced by " << amount << ".";
        lives_ -= amount;
        if (lives_ < 0) lives_ = 0;
        logger_.info() << "[" << name_ << "] " << "now has " <<
            getLivesAsString() << " left.";
        if(lives_ <= 0) {
            logger_.info() << "[" << name_ << "] " << "has to leave the game!";
        }
        return lives_ > 0;
    }


    /**
     * @brief Assigns a MeiernDiceCup to the player.
     * @param cup A pointer to the MeiernDiceCup to assign.
     */
    void setDiceCup(MeiernDiceCup* cup) { diceCup_ = cup; }


    /**
     * @brief Retrieves the player's assigned MeiernDiceCup.
     * @return A pointer to the MeiernDiceCup, or nullptr if none is assigned.
     */
    MeiernDiceCup* getDiceCup() const { return diceCup_; }

    // Game actions
    virtual Announcement performTurn(Announcement previousAnnouncement) = 0;
    virtual Announcement announceValue(Announcement announcement) = 0;
    virtual bool trustPreviousAnnouncement() = 0;
    virtual bool doubtPreviousAnnouncement() = 0;
    virtual bool trustsAnnouncement(Announcement announcement, Announcement previousAnnouncement) = 0;
};
