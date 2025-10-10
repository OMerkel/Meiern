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

void Game::handoverDiceCup( CyclicList<Player>::iterator nextPlayer ) {
	MeiernDiceCup* cup = currentPlayer->getDiceCup();
	nextPlayer->setDiceCup(cup);
}

std::string Game::runLoop() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 2);

	const Announcement MEIER = Announcement(2, 1);
	const Announcement INVALID = Announcement(0, 0);
	Announcement previousAnnouncement = Announcement(0, 0); // No previous announcement
    while (isRunning) {
        displayCurrentPlayers();
		// int announced_value = dist(gen);
		Announcement announcement = currentPlayer->performTurn(previousAnnouncement);
        if (announcement == MEIER) {
			if (currentPlayer->getDiceCup()->getDiceValue() == MEIER) {
				Interaction::output("Indeed! " + currentPlayer->getName() +
				    " reveals MEIER in the dice cup!");
			}
			else {
				Interaction::output("Error: Current player " +
				                    currentPlayer->getName() +
				                    " announced MEIER but did not roll it!");
				bool alive = currentPlayer->decreaseLives();
				if (!alive) {
					auto nextPlayer = playerList.next(currentPlayer);
					playerList.erase(currentPlayer);
					currentPlayer = nextPlayer;
				}
				if (playerList.size() == 1) {
					isRunning = false;
					continue;
				}
				previousAnnouncement = Announcement(0, 0); // Reset previous announcement
				continue;
			}
			auto nextPlayer = playerList.next(currentPlayer);
			bool alive = nextPlayer->decreaseLives();
			if (!alive) {
				playerList.erase(nextPlayer);
				if (playerList.size() == 1) {
					isRunning = false;
					break;
				}
			}
			previousAnnouncement = Announcement(0, 0); // Reset previous announcement
			continue;
		}
		if (announcement == INVALID) {
			Interaction::output("Error: Invalid announcement. Same player should try again.");
			continue;
		}
		bool trust_announcement = (dist(gen) == 1);
		Interaction::output("Does " + playerList.next(currentPlayer)->getName() +
		                    " trust the announcement? " +
			                std::string(trust_announcement ? "Yes" : "No"));
		if (trust_announcement) {
			playerList.next(currentPlayer)->trustPreviousAnnouncement();
			handoverDiceCup(playerList.next(currentPlayer));
			currentPlayer = playerList.next(currentPlayer);
			previousAnnouncement = announcement;
		}
		else {
			playerList.next(currentPlayer)->doubtPreviousAnnouncement();
			
			// bool reduce_current = (dist(gen) == 1);
			bool reduce_current = currentPlayer->getDiceCup()->getDiceValue() <= previousAnnouncement;

			auto next_player = playerList.next(currentPlayer);
			if (reduce_current) {
			    bool alive = currentPlayer->decreaseLives();
				handoverDiceCup(next_player);
				if (!alive) {
					playerList.erase(currentPlayer);
				}
				currentPlayer = next_player;
			}
			else {
				bool alive = next_player->decreaseLives();
				if (!alive) {
					playerList.erase(next_player);
					next_player = playerList.next(currentPlayer);
				}
				handoverDiceCup(next_player);
				currentPlayer = next_player;
			}
			if (playerList.size() == 1) {
				isRunning = false;
				continue;
			}
			previousAnnouncement = Announcement(0, 0); // Reset previous announcement
		}
	}
	std::string winnerMessage = "Congratulations! Winner of the game is " +
		currentPlayer->getName() + " with " +
        currentPlayer->getLivesAsString() + " left.";
	Interaction::output(winnerMessage);
	return winnerMessage;
}

void Game::setup(std::string playerName) {
    isRunning = true;
	playerList.clear();
	std::string name = playerName.empty() ? Interaction::ask_name() : playerName;
    playerList.push_back(Player("Alice", 3));
    playerList.push_back(Player("Bob", 3));
    playerList.push_back(Player("Charlie", 3));
    playerList.push_back(Player(name, 3)); // Add the user's name
	Greeting greeting(name);
	Interaction::output(greeting.get_greeting());

    currentPlayer = playerList.begin();
	currentPlayer->setDiceCup(new MeiernDiceCup());
}
