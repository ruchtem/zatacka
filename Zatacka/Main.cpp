#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "PlayerSelection.h"
#include "GameOver.h"

using namespace std;
using namespace sf;

enum GameStages {
	SelectPlayers = 0,
	CurvesRunning = 1,
	GameIsOver = 2
};

int maxScore(vector<Player*> players) { //What is the highest score
	int maxScore = 0;
	for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
		if (players.at(i)->getScore() > maxScore) {
			maxScore = players.at(i)->getScore();
		}
	}
	return maxScore;
}

int main() {


	Font font;
	if (!font.loadFromFile("resources/arial.ttf"))	// Necessary to render text
		throw exception("Could not load font!");

	RenderWindow* window = new RenderWindow(VideoMode(800, 600), "Achtung - die Kurve!");
	window->setFramerateLimit(60);
	bool fullscreen = false;

	GameStages stage = SelectPlayers;

	PlayerSelection playerSelection = PlayerSelection(window, &font);
	
	vector<Player*> players;

	GameOver gameover = GameOver(window, &font, players);
	

	int collidedCounter = 0;

	Vertex leftBorder[2];
	leftBorder[0].position = sf::Vector2f(window->getSize().x / 100 * 7, 0);
	leftBorder[0].color = sf::Color::Magenta;
	leftBorder[1].position = sf::Vector2f(window->getSize().x / 100 * 7, window->getSize().y);
	leftBorder[1].color = sf::Color::Magenta;

	// main loop
	while (window->isOpen())		
	{
		// Handle events
		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();

			if (stage == SelectPlayers)
				playerSelection.processEvent(event);

			if (stage == GameIsOver) {
				gameover.processEvent(event);
			}
		}


		//Create a screenshot of the game before moving
		sf::Vector2u windowSize = window->getSize();
		sf::Texture texture;
		texture.create(windowSize.x, windowSize.y);
		texture.update(*window);
		sf::Image screenshot = texture.copyToImage();

		// Controll game flow
		switch (stage) {
		case SelectPlayers:
			if (playerSelection.isFinished()) {
				players = playerSelection.getPlayers();
				stage = CurvesRunning;
			}
			break;

		case CurvesRunning:
			for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
				if (!players.at(i)->getCollided()) // Only move, if not collided
					players.at(i)->move();			
			}
			if (collidedCounter == players.size()) {
				stage = GameIsOver;
				break;
			}
			for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
				if (!players.at(i)->getCollided()) { //Collision already happened?
					bool collision = (players.at(i)->collision(screenshot, players, windowSize));
					players.at(i)->setCollided(collision);
					if (collision) {
						players.at(i)->setScore(players.at(i)->getScore() + collidedCounter); //score ranges from 0 to amount of players-1
						collidedCounter++; //Next player gets a higher score
					}
				}
			}
			break;

		case GameIsOver:
			if (gameover.isNewGame()) {
				gameover.initiateNewGame();
				stage = SelectPlayers;
				playerSelection.prepareNewGame();
			}
			collidedCounter = 0;
			if (maxScore(players) > 10) {
				stage = GameIsOver; //Game is either finished...
			}
			else {
				for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
					players.at(i)->nextRound(windowSize); //...or a new round should start
				}
				stage = CurvesRunning;
			}
			break;
		}

		
		if (playerSelection.isFullscreen() && !fullscreen) {
			fullscreen = true;
			window->close();
			delete window;
			window = new RenderWindow(VideoMode::getDesktopMode(), "Achtung - die Kurve!", Style::fullscreen);
			window->setFramerateLimit(60);
		}
		else if (!playerSelection.isFullscreen() && fullscreen) {
				fullscreen = false;
				window->close();
				delete window;
				window = new RenderWindow(VideoMode(800, 600), "Achtung - die Kurve!");
				window->setFramerateLimit(60);
		}


		// Draw everything

		window->clear();

		switch (stage) {
		case SelectPlayers:
			playerSelection.draw();
			break;

		case CurvesRunning:
			for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
				players.at(i)->draw(window, &font, i);

			}
			window->draw(leftBorder, 4, sf::Lines);
			break;

		case GameIsOver:
			//GameOver gameover = GameOver(window, &font, players);
			gameover.setPlayers(players);
			gameover.draw();
			break;
		}

		window->display();
	}

	// Clear memory
	for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
		delete players.at(i); players.at(i) = NULL;
	}

	delete window; window = NULL;

	return 0;
}


