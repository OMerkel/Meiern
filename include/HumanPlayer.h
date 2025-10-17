/**
 * @file HumanPlayer.h
 * @brief Declaration of the HumanPlayer class.
 * 
 * This file contains the definition of the HumanPlayer class,
 * which represents a human player in the Meiern dice game.
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
#include <iostream>

#include "AbstractPlayer.h"
#include "Logger.h"

class HumanPlayer : public AbstractPlayer {
    Logger& logger = Logger::instance();

public:
    /**
     * @brief Constructs a Player with a given name and initial number of lives.
     * @param name The name of the player.
     * @param initialLives The initial number of lives for the player.
     */
    HumanPlayer(const std::string& name, int initialLives)
        : AbstractPlayer(name, initialLives) {
        logger.info() << "[" << getName() << "] " << "got created with " <<
            getLivesAsString() << ".";
    }

    
    /**
     * @brief Performs the player's turn by shaking the dice cup and making an announcement.
     * @param previousAnnouncement The previous announcement made in the game.
     * @return The new announcement made by the player.
     */
    Announcement performTurn(Announcement previousAnnouncement) override {
        if (!diceCup) {
            logger.error() << "[" << name << "] " << "Error: No dice cup assigned to player " << name;
            return Announcement(0, 0); // Error case
        }
        if (previousAnnouncement.getValue() != 0) {
            logger.info() << "[" << name << "] " << "got a previous announcement of " <<
                previousAnnouncement.getValue();
        }
        else {
            logger.info() << "[" << name << "] " << "got no previous announcement.";
        }

        logger.info() << "[" << name << "] " << "is shaking the dice cup.";
        Announcement diceValue = diceCup->shake();
        logger.debug() << "[" << name << "] " << "rolled: " <<
            diceValue.getValue();

        const Announcement MEIER = Announcement(2, 1);
        if (diceValue == MEIER) {
            logger.info() << "[" << name << "] " <<
                "announces MEIER and claims a win of this round immediately!";
        }
        else {
            if (previousAnnouncement.getValue() != 0 &&
                !(diceValue > previousAnnouncement)) {
                logger.debug() << "[" << name << "] " <<
                    "cannot announce a lower or equal value than the previous announcement!";
                logger.debug() << "[" << name << "] " <<
                    "must announce at least: " <<
                    previousAnnouncement.nextHigher().getValue();
                std::vector<Announcement> remainingAnnouncements = previousAnnouncement.allHigher();
                if (remainingAnnouncements.empty()) {
                    logger.error() << "[" << name << "] " <<
                        "Error: No higher announcement possible!";
                    return Announcement(0, 0); // Error case
                }
                if (remainingAnnouncements.size() == 1) {
                    diceValue = remainingAnnouncements[0];
                }
                else {
                    // More than one possible announcement


int choice = 0;


                    diceValue = remainingAnnouncements[choice];
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
        logger.info() << "[" << name << "] " << "announces value: " << announcement.getValue();
        return announcement;
    }


    /**
     * @brief Indicates that the player trusts the previous announcement.
     * @return true if the player trusts the announcement, false otherwise.
     */
    bool trustPreviousAnnouncement() override {
        char input;
        std::cout << name << ", do you trust the previous announcement? (y/n): ";
        std::cin >> input;
        return (input == 'y' || input == 'Y');
    }

    /**
     * @brief Indicates that the player doubts the previous announcement.
     * @return true if the player doubts the announcement, false otherwise.
     */
    bool doubtPreviousAnnouncement() override {
        char input;
        std::cout << name << ", do you doubt the previous announcement? (y/n): ";
        std::cin >> input;
        return (input == 'y' || input == 'Y');
    }
};
