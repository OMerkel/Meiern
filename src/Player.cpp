#include "Player.h"
#include <iostream>

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

void Player::announceValue(int value) {
	std::cout << name << " announces value: " << value << std::endl;
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
