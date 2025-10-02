#include "Game.h"

Game::Game() : isRunning(false) {}

void Game::displayCurrentPlayers() {
    Interaction::output("Remaining players:");
    CyclicList<Player>::iterator player = currentPlayer;
    do {
		Interaction::output("- " + player->getName() + " with " +
        	player->getLivesAsString());
		player=playerList.next(player);
    } while (player != currentPlayer);
    Interaction::output("Current player: " + currentPlayer->getName());
    Interaction::output("Next player: " +
        playerList.next(currentPlayer)->getName());
}

void Game::runLoop() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 2);

	Announcement previousAnnouncement = Announcement(0, 0); // No previous announcement
    while (isRunning) {
        displayCurrentPlayers();
		// int announced_value = dist(gen);
		Announcement announcement = currentPlayer->performTurn(previousAnnouncement);
		bool trust_announcement = (dist(gen) == 1);
		Interaction::output("Does " + playerList.next(currentPlayer)->getName() +
		                    " trust the announcement? " +
			                std::string(trust_announcement ? "Yes" : "No"));
		if (trust_announcement) {
			playerList.next(currentPlayer)->trustPreviousAnnouncement();
			MeiernDiceCup* cup = currentPlayer->getDiceCup();
			previousAnnouncement = announcement;
			currentPlayer = playerList.next(currentPlayer);
			currentPlayer->setDiceCup(cup);
		}
		else {
			playerList.next(currentPlayer)->doubtPreviousAnnouncement();
			// Randomly decide either current or next player looses a life
			bool reduce_current = (dist(gen) == 1);
			auto to_reduce_life = reduce_current ? currentPlayer :
			    playerList.next(currentPlayer);
			auto next_player = to_reduce_life->getLives()>1 ? to_reduce_life :
			    (reduce_current && to_reduce_life->getLives()==1 ?
				playerList.next(currentPlayer) : currentPlayer);
			Interaction::output("Reducing lives of player " +
				                to_reduce_life->getName());
			to_reduce_life->decreaseLives();
			Interaction::output(to_reduce_life->getName() + " now has " +
			                    to_reduce_life->getLivesAsString() + " left.");
			if(to_reduce_life->getLives() <= 0) {
				Interaction::output(to_reduce_life->getName() +
				                    " has to leave the game!");
				playerList.erase(to_reduce_life);
				if (playerList.size() == 1) {
                    isRunning = false;
                }
			}
			MeiernDiceCup* cup = currentPlayer->getDiceCup();
			previousAnnouncement = Announcement(0, 0); // Reset previous announcement
			currentPlayer = next_player;
			currentPlayer->setDiceCup(cup);
		}
	}
	Interaction::output("Winner is " + currentPlayer->getName() + " with " +
                        currentPlayer->getLivesAsString() + " left.");
}

void Game::setup() {
    isRunning = true;
    std::string name = Interaction::ask_name();
    playerList.push_back(Player("Alice", 3));
    playerList.push_back(Player("Bob", 3));
    playerList.push_back(Player("Charlie", 3));
    playerList.push_back(Player(name, 3)); // Add the user's name
	Greeting greeting(name);
	Interaction::output(greeting.get_greeting());

    currentPlayer = playerList.begin();
	currentPlayer->setDiceCup(new MeiernDiceCup());
}
