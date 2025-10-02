#pragma once
#include <iostream>
#include <string>
#include "MeiernDiceCup.h"
#include "Announcement.h"

class Player {
private:
	std::string name;
	int lives;
	MeiernDiceCup* diceCup = nullptr;

public:
	Player(const std::string& name, int initialLives);
	const std::string& getName() const;
	int getLives() const;
	std::string getLivesAsString() const;
	void increaseLives(int amount = 1);
	void decreaseLives(int amount = 1);

	// Dice cup management
	void setDiceCup(MeiernDiceCup* cup);
	MeiernDiceCup* getDiceCup() const;

	// Game actions
	Announcement performTurn(Announcement previousAnnouncement);
	int announceValue(int diceValue);
	bool trustPreviousAnnouncement();
	bool doubtPreviousAnnouncement();
};
