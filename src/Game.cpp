/**
 * @file Game.cpp
 * @brief Implementation of the Game class for the Meiern dice game.
 *
 * This file contains the core logic for running a Meiern dice game,
 * including player management, turn handling, dice cup handover, and
 * game loop execution. The Game class utilizes a cyclic list
 * of Player objects to manage turns and player elimination.
 * The game loop processes player actions,
 * announcements, trust/doubt decisions, and determines the winner.
 *
 * Main functionalities:
 * - Displaying current players and their status.
 * - Handling dice cup handover between players.
 * - Running the main game loop, including announcement validation and
 *   player elimination.
 * - Setting up the game with initial players and dice cups.
 *
 * Classes used:
 * - Game: Manages the overall game state and flow.
 * - Player: Represents a participant in the game.
 * - MeiernDiceCup: Represents the dice cup used in the game.
 * - Announcement: Represents a player's announcement during their turn.
 * - CyclicList: A cyclic container for managing player turns.
 * - Interaction: Handles input/output operations.
 * - Greeting: Provides greeting messages for players.
 *
 * @author Oliver Merkel
 * @date 2025-10-10
 */
#include "Game.h"

Game::Game() : isRunning(false), previousAnnouncement(0, 0),
	logger(Logger::instance()) {
	logger.enableConsole(true);
	logger.setConsoleLevel(Logger::Level::Info);
	logger.enableFile(true);
	logger.setFileLevel(Logger::Level::Debug);
	logger.setLogFile("game.log", false);
}

void Game::displayCurrentPlayers() {
    logger.info() << "[" << className << "] " << "Remaining players:";
    CyclicList<Player>::iterator player = currentPlayer;
    do {
		logger.info() << "[" << className << "] " << "- " << player->getName() << " with " <<
        	player->getLivesAsString();
		player=playerList.next(player);
    } while (player != currentPlayer);
    logger.info() << "[" << className << "] " << "Current player: " << currentPlayer->getName();
    logger.info() << "[" << className << "] " << "Next player: " << 
	    playerList.next(currentPlayer)->getName();
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
	previousAnnouncement = Announcement(0, 0); // No previous announcement
    while (isRunning) {
        displayCurrentPlayers();
		// int announced_value = dist(gen);
		Announcement announcement = currentPlayer->performTurn(previousAnnouncement);
        if (announcement == MEIER) {
			if (currentPlayer->getDiceCup()->getDiceValue() == MEIER) {
				logger.info() << "[" << className << "] " << "Indeed! " << currentPlayer->getName() <<
				    " reveals MEIER in the dice cup!";
			}
			else {
				logger.info() << "[" << className << "] " << "Error: Current player " <<
				    currentPlayer->getName() <<
					" announced MEIER but did not roll it!";
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
			logger.error() << "[" << className << "] " << "Error: Invalid announcement. " <<
			    "Same player should try again.";
			continue;
		}
		bool trust_announcement = (dist(gen) == 1);
		logger.info() << "[" << className << "] " << "Does " << playerList.next(currentPlayer)->getName() <<
		    " trust the announcement? " << std::string(trust_announcement ? "Yes" : "No");
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
	logger.info() << "[" << className << "] " << winnerMessage;
	return winnerMessage;}

void Game::setup(std::string playerName) {
	isRunning = true;
	playerList.clear();
	std::string name = playerName.empty() ? Interaction::ask_name() : playerName;
	playerList.push_back(Player("Alice", 3));
	playerList.push_back(Player("Bob", 3));
	playerList.push_back(Player("Charlie", 3));
	playerList.push_back(Player(name, 3));
	Greeting greeting(name);
	logger.info() << "[" << className << "] " << greeting.get_greeting();
	logger.debug() << "[" << className << "] " << greeting.get_greeting();

	currentPlayer = playerList.begin();
	currentPlayer->setDiceCup(new MeiernDiceCup());
}
