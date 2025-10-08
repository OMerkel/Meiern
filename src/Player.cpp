#include "Player.h"

Player::Player(const std::string& name, int initialLives)
	: name(name), lives(initialLives) {}

const std::string& Player::getName() const {
	return name;
}

int Player::getLives() const {
	return lives;
}

std::string Player::getLivesAsString() const {
	return std::to_string(lives) + (lives == 1 ? " life" : " lives");
}

void Player::increaseLives(int amount) {
	lives += amount;
}

bool Player::decreaseLives(int amount) {
	/** Decrease the player's lives by the specified amount.
	 * 
	 * @return true if the player is still alive (lives > 0),
	 *         false if the player has no lives left.
	 */
	Interaction::output("Reducing lives of player " + name);
	lives -= amount;
	if (lives < 0) lives = 0;
	Interaction::output(name + " now has " + getLivesAsString() + " left.");
	if(lives <= 0) {
		Interaction::output(name + " has to leave the game!");
	}
	return lives > 0;
}

int Player::announceValue(int diceValue) {
	Interaction::output(name + " announces value: " +
		std::to_string(diceValue));
	return diceValue;
}

Announcement Player::performTurn(Announcement previousAnnouncement) {
	if (diceCup) {
		Announcement diceValue = diceCup->shake();
		if (previousAnnouncement.getValue() != 0) {
			Interaction::output("Previous announcement was: " +
				std::to_string(previousAnnouncement.getValue()));
		}
		else {
			Interaction::output("No previous announcement.");
		}
		Interaction::output("(" + name + " rolled: " +
			std::to_string(diceValue.getValue()) + ")");
		const Announcement MEIER = Announcement(2, 1);
		if (diceValue == MEIER) {
			Interaction::output(name +
			    " announces MEIER and claims a win of this round immediately!");
		}
		else {
			Interaction::output(name + " announces: " +
				std::to_string(diceValue.getValue()));
		}
		return diceValue;
	}
	Interaction::output("Error: No dice cup assigned to player " + name);
	return Announcement(0, 0); // Error case
}

bool Player::trustPreviousAnnouncement() {
	// Placeholder logic
	Interaction::output(name + " trusts the previous announcement.");
	return true;
}

bool Player::doubtPreviousAnnouncement() {
	// Placeholder logic
	Interaction::output(name + " doubts the previous announcement!");
	return true;
}

void Player::setDiceCup(MeiernDiceCup* cup) {
	diceCup = cup;
}

MeiernDiceCup* Player::getDiceCup() const {
	return diceCup;
}
