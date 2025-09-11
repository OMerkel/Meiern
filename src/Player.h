#pragma once
#include <string>

class Player {
private:
	std::string name;
	int lives;

public:
	Player(const std::string& name, int initialLives);
	const std::string& getName() const;
	int getLives() const;
	std::string getLivesAsString() const;
	void increaseLives(int amount = 1);
	void decreaseLives(int amount = 1);

	// Game actions
	void announceValue(int value);
	bool trustPreviousAnnouncement();
	bool doubtPreviousAnnouncement();
};
