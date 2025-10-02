#include "Die.h"

// Die implementation
std::mt19937 Die::rng(static_cast<unsigned int>(std::time(nullptr)));

Die::Die(int sides) : sides(sides) {
	roll();
}

int Die::roll() {
	std::uniform_int_distribution<int> dist(1, sides);
	value = dist(rng);
	return value;
}

int Die::getValue() const {
	return value;
}
