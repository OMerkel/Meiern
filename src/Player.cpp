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

void Player::decreaseLives(int amount) {
	lives -= amount;
	if (lives < 0) lives = 0;
}

int Player::announceValue(int diceValue) {
	std::cout << name << " announces value: " << diceValue << std::endl;
	return diceValue;
}

Announcement Player::performTurn(Announcement previousAnnouncement) {
	if (diceCup) {
		Announcement diceValue = diceCup->shake();
		if (previousAnnouncement.getValue() != 0)
			std::cout << "Previous announcement was: " << previousAnnouncement.getValue() << std::endl;
		else
			std::cout << "No previous announcement." << std::endl;
		std::cout << "(" << name << " rolled: " << diceValue.getValue() << ")" << std::endl;
		std::cout << name << " announces: " << diceValue.getValue() << std::endl;
		return diceValue;
	}
	std::cerr << "Error: No dice cup assigned to player " << name << std::endl;
	return Announcement(0, 0); // Error case
}

bool Player::trustPreviousAnnouncement() {
	// Placeholder logic
	std::cout << name << " trusts the previous announcement." << std::endl;
	return true;
}

bool Player::doubtPreviousAnnouncement() {
	// Placeholder logic
	std::cout << name << " doubts the previous announcement!" << std::endl;
	return true;
}

void Player::setDiceCup(MeiernDiceCup* cup) {
	diceCup = cup;
}

MeiernDiceCup* Player::getDiceCup() const {
	return diceCup;
}
