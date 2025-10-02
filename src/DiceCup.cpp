#include "DiceCup.h"

// DiceCup implementation
DiceCup::DiceCup(int initialDice) {
	for (int i = 0; i < initialDice; ++i) {
		dice.push_back(std::make_unique<Die>());
	}
}

void DiceCup::shake() {
	for (auto& die : dice) {
		die->roll();
	}
}

void DiceCup::addDie(int sides) {
	dice.push_back(std::make_unique<Die>(sides));
}

void DiceCup::removeDie(size_t index) {
	if (index < dice.size()) {
		dice.erase(dice.begin() + index);
	}
}

size_t DiceCup::getDiceCount() const {
	return dice.size();
}

const Die* DiceCup::getDie(size_t index) const {
	if (index < dice.size()) {
		return dice[index].get();
	}
	return nullptr;
}
