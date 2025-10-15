/**
 * @class Player
 * @brief Represents a player in the Meiern dice game.
 *
 * The Player class encapsulates the state and behavior of a player, including their name,
 * current number of lives, and interaction with the dice cup. It provides methods for
 * managing lives, performing turns, announcing dice values, and interacting with game
 * announcements.
 *
 * @author Oliver Merkel
 * @date 2025-10-10
 *
 * @note This class relies on the Interaction, Announcement, and MeiernDiceCup classes
 *       for game logic and output.
 */
#include "Player.h"


/**
 * @brief Constructs a Player with a given name and initial number of lives.
 * @param name The name of the player.
 * @param initialLives The initial number of lives for the player.
 */
Player::Player(const std::string& name, int initialLives) :
	name(name), lives(initialLives), logger(Logger::instance()) {
	logger.info() << "[" << className << "] " << "Created player: " << name << " with " <<
		getLivesAsString();
}


/**
 * @brief Retrieves the name of the player.
 * @return The player's name as a constant reference to a string.
 */
const std::string& Player::getName() const {
	return name;
}


/**
 * @brief Retrieves the current number of lives the player has.
 * @return The number of lives as an integer.
 */
int Player::getLives() const {
	return lives;
}


/**
 * @brief Retrieves the player's lives as a formatted string.
 * @return A string representing the number of lives, e.g., "3 lives" or "1 life".
 */
std::string Player::getLivesAsString() const {
	return std::to_string(lives) + (lives == 1 ? " life" : " lives");
}


/**
 * @brief Increases the player's lives by a specified amount.
 * @param amount The number of lives to add (default is 1).
 */
void Player::increaseLives(int amount) {
	lives += amount;
}


/**
 * @brief Decreases the player's lives by a specified amount.
 * @param amount The number of lives to subtract (default is 1).
 * @return true if the player is still alive (lives > 0),
 *         false if the player has no lives left.
 */
bool Player::decreaseLives(int amount) {
	/** Decrease the player's lives by the specified amount.
	 * 
	 * @return true if the player is still alive (lives > 0),
	 *         false if the player has no lives left.
	 */
	logger.info() << "[" << className << "] " << "Reducing lives of player " << name;
	lives -= amount;
	if (lives < 0) lives = 0;
	logger.info() << "[" << className << "] " << name << " now has " <<
	    getLivesAsString() << " left.";
	if(lives <= 0) {
		logger.info() << "[" << className << "] " << name << " has to leave the game!";
	}
	return lives > 0;
}


/**
 * @brief Announces a dice value.
 * @param diceValue The value to announce.
 * @return The announced dice value.
 */
int Player::announceValue(int diceValue) {
	logger.info() << "[" << className << "] " << name << " announces value: " <<
		diceValue;
	return diceValue;
}


/**
 * @brief Performs the player's turn by shaking the dice cup and making an announcement.
 * @param previousAnnouncement The previous announcement made in the game.
 * @return The new announcement made by the player.
 */
Announcement Player::performTurn(Announcement previousAnnouncement) {
	if (!diceCup) {
		logger.error() << "[" << className << "] " << "Error: No dice cup assigned to player " << name;
		return Announcement(0, 0); // Error case
	}
	if (previousAnnouncement.getValue() != 0) {
		logger.info() << "[" << className << "] " << "Previous announcement was: " <<
			previousAnnouncement.getValue();
	}
	else {
		logger.info() << "[" << className << "] " << "No previous announcement.";
	}

	Announcement diceValue = diceCup->shake();
	logger.debug() << "[" << className << "] " << name << " rolled: " <<
		diceValue.getValue();
	const Announcement MEIER = Announcement(2, 1);
	if (diceValue == MEIER) {
		logger.info() << "[" << className << "] " << name <<
			" announces MEIER and claims a win of this round immediately!";
	}
	else {
		if (previousAnnouncement.getValue() != 0 &&
			!(diceValue > previousAnnouncement)) {
			logger.debug() << "[" << className << "] " << name <<
				" cannot announce a lower or equal value than the previous announcement!";
			logger.debug() << "[" << className << "] " << name <<
				" must announce at least: " <<
				previousAnnouncement.nextHigher().getValue();
			std::vector<Announcement> remainingAnnouncements = previousAnnouncement.allHigher();
			if (remainingAnnouncements.empty()) {
				logger.error() << "[" << className << "] " << "Error: No higher announcement possible!";
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
				std::uniform_int_distribution<> dis(0, cheatSize);
				diceValue = remainingAnnouncements[dis(gen)];
			}
		}
		logger.info() << "[" << className << "] " << name << " announces: " <<
			diceValue.getValue();
	}
	return diceValue;
}


/**
 * @brief Indicates that the player trusts the previous announcement.
 * @return true if the player trusts the announcement, false otherwise.
 */
bool Player::trustPreviousAnnouncement() {
	// Placeholder logic
	logger.info() << "[" << className << "] " << name << " trusts the previous announcement.";
	return true;
}


/**
 * @brief Indicates that the player doubts the previous announcement.
 * @return true if the player doubts the announcement, false otherwise.
 */
bool Player::doubtPreviousAnnouncement() {
	// Placeholder logic
	logger.info() << "[" << className << "] " << name << " doubts the previous announcement!";
	return true;
}


/**
 * @brief Assigns a MeiernDiceCup to the player.
 * @param cup A pointer to the MeiernDiceCup to assign.
 */
void Player::setDiceCup(MeiernDiceCup* cup) {
	diceCup = cup;
}


/**
 * @brief Retrieves the player's assigned MeiernDiceCup.
 * @return A pointer to the MeiernDiceCup, or nullptr if none is assigned.
 */
MeiernDiceCup* Player::getDiceCup() const {
	return diceCup;
}
