/**
 * @file AIPlayerSimple.h
 * @brief Declaration of the AIPlayerSimple class.
 * 
 * This file contains the definition of the AIPlayerSimple class,
 * which is a simple AI implementation of a player in the Meiern dice game.
 * It inherits from the AbstractPlayer class and implements
 * methods for performing turns, making announcements, and
 * handling user input on the console.
 *
 * The Player class encapsulates the state and behavior of a player, including their name,
 * current number of lives, and interaction with the dice cup. It provides methods for
 * managing lives, performing turns, announcing dice values, and interacting with game
 * announcements.
 *
 * @author Oliver Merkel
 * @date 2025-10-14
 */
#pragma once
#include <random>
#include <iostream>

#include "AbstractPlayer.h"
#include "Logger.h"

class AIPlayerSimple : public AbstractPlayer {
    Logger& logger = Logger::instance();

public:
    /**
     * @brief Constructs a Player with a given name and initial number of lives.
     * @param name The name of the player.
     * @param initialLives The initial number of lives for the player.
     */
    AIPlayerSimple(const std::string& name, int initialLives)
        : AbstractPlayer(name + " (AI)", initialLives) {
        logger.info() << "[" << getName() << "] " << "got created with " <<
            getLivesAsString() << ".";
    }

    
    /**
     * @brief Performs the player's turn by shaking the dice cup and making an announcement.
     * @param previousAnnouncement The previous announcement made in the game.
     * @return The new announcement made by the player.
     */
    Announcement performTurn(Announcement previousAnnouncement) override {
        if (!diceCup_) {
            logger_.error() << "[" << name_ << "] " << "Error: No dice cup assigned to player " << name_;
            return Announcement(0, 0); // Error case
        }
        if (previousAnnouncement.getValue() != 0) {
            logger_.info() << "[" << name_ << "] " << "got a previous announcement of " <<
                previousAnnouncement.getValue();
        }
        else {
            logger_.info() << "[" << name_ << "] " << "got no previous announcement.";
        }

        logger_.info() << "[" << name_ << "] " << "is shaking the dice cup.";
        Announcement diceValue = diceCup_->shake();
        logger_.debug() << "[" << name_ << "] " << "rolled: " <<
            diceValue.getValue();

        const Announcement MEIER = Announcement(2, 1);
        if (diceValue == MEIER) {
            logger_.info() << "[" << name_ << "] " <<
                "announces MEIER and claims a win of this round immediately!";
        }
        else {
            if (previousAnnouncement.getValue() != 0 &&
                !(diceValue > previousAnnouncement)) {
                logger_.debug() << "[" << name_ << "] " <<
                    "cannot announce a lower or equal value than the previous announcement!";
                logger_.debug() << "[" << name_ << "] " <<
                    "must announce at least: " <<
                    previousAnnouncement.nextHigher().getValue();
                std::vector<Announcement> remainingAnnouncements = previousAnnouncement.allHigher();
                if (remainingAnnouncements.empty()) {
                    logger_.error() << "[" << name_ << "] " <<
                        "Error: No higher announcement possible!";
                    return Announcement(0, 0); // Error case
                }
                if (remainingAnnouncements.size() == 1) {
                    diceValue = remainingAnnouncements[0];
                }
                else {
                    // More than one possible announcement
                    // Cheat a bit by not choosing from the full range
                    // but only randomly from the lower half of the remaining announcements
                    // to increase the chance of winning
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    // reduced range to exclude MEIER (thus -2 instead of -1)
                    size_t remainingSize = remainingAnnouncements.size() - 2;
                    // cheat but not being too obvious
                    size_t cheatSize = remainingSize / 2;
                    std::uniform_int_distribution<> dis(0, static_cast<int>(cheatSize));
                    diceValue = remainingAnnouncements[dis(gen)];
                }
            }
        }
        return announceValue(diceValue);
    }


    /**
     * @brief Announces a dice value.
     * @param announcement The value to announce.
     * @return The announced itself.
     */
    Announcement announceValue(Announcement announcement) override {
        logger_.info() << "[" << name_ << "] " << "announces value: " << announcement.getValue();
        return announcement;
    }


    /**
     * @brief Indicates that the player trusts the previous announcement.
     * @return true if the player trusts the announcement, false otherwise.
     */
    bool trustPreviousAnnouncement() override {
        logger_.info() << "[" << name_ << "] " << "trusts the previous announcement.";
        return true;
    }

    /**
     * @brief Indicates that the player doubts the previous announcement.
     * @return true if the player doubts the announcement, false otherwise.
     */
    bool doubtPreviousAnnouncement() override {
        logger_.info() << "[" << name_ << "] " << "doubts the previous announcement.";
        return true;
    }

    /**
     * @brief Decides whether to trust a given announcement.
     * @param announcement The announcement to evaluate.
     * @return true if the player decides to trust the announcement, false otherwise.
     */
    bool trustsAnnouncement(Announcement announcement, Announcement previousAnnouncement) override {
        Announcement noPrevious = Announcement(0, 0);
        Announcement easyGoing = Announcement(4, 3); // value 43
        if (announcement <= easyGoing) {
            logger_.debug() << "[" << name_ << "] " << "easy going announcement of " <<
                announcement.getValue() << ", trusts automatically.";
            return true;
        }
        if (previousAnnouncement == noPrevious) {
            // No previous announcement, trust by 80%
            logger_.debug() << "[" << name_ << "] " << "no previous announcement, trusts by 80%.";
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 100);
            return dis(gen) <= 80;
        }
        static MeiernDiceCup cup;
        cup.shake();
        Announcement myComparisonRoll = cup.getDiceValue();
        logger_.debug() << "[" << name_ << "] " << "comparison roll is " <<
            myComparisonRoll.getValue() << " against announced " <<
            announcement.getValue() << ".";

        // Is it likely enough to trust the announcement?
        if (myComparisonRoll > announcement) {
            logger_.debug() << "[" << name_ << "] " << "decides to trust the announcement of " <<
                announcement.getValue() << ".";
            return true;
        }
        else {
            logger_.debug() << "[" << name_ << "] " << "decides to doubt the announcement of " <<
                announcement.getValue() << ".";
            return false;
        }
    }
};
