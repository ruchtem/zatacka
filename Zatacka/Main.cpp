#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "PlayerSelection.h"
#include "GameOver.h"
#include "Icon.h"
#include "IconManager.h"


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

void showCountdown(Text countdown, RenderWindow* window) { //Draw a countdown -> Draw a number and let the screen freeze for one second
	sf::Vector2u windowSize = window->getSize();
	countdown.setPosition(windowSize.x / 2 - 48, windowSize.y / 2 - 48);
	countdown.setString("3");
	window->clear();
	window->draw(countdown);
	window->display();
	sleep(seconds(1));
	window->clear();
	countdown.setString("2");
	window->draw(countdown);
	window->display();
	sleep(seconds(1));
	window->clear();
	countdown.setString("1");
	window->draw(countdown);
	window->display();
	sleep(seconds(1));
}

int main() {


	srand(time(0)); //Initializing rand for better pseudo random starting positions


	Font font;
	if (!font.loadFromFile("resources/arial.ttf"))	// Necessary to render text
		throw exception("Could not load font!");

	RenderWindow* window = new RenderWindow(VideoMode(800, 600), "Achtung - die Kurve!");
	window->setFramerateLimit(60);
	bool fullscreen = false;

	GameStages stage = SelectPlayers;

	PlayerSelection playerSelection = PlayerSelection(window, &font);
	IconManager iconManager = IconManager(window);

	vector<Player*> players;

	GameOver gameover = GameOver(window, &font);

	bool startCountdown = false;
	bool speedDynamization = false;
	
	int winningScore = 0;

	Text countdown;
	countdown.setFont(font);
	countdown.setCharacterSize(144);
	countdown.setFillColor(Color::Red);
	countdown.setStyle(Text::Bold);

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
		case SelectPlayers: //Players have to get selected
			if (playerSelection.isFinished()) {
				speedDynamization = playerSelection.dynamizeSpeed(); //Should the speed be increased after each round?
				Player::dynamizationRate = playerSelection.getStartSpeed(); //Set the start speed: "langsam", "mittel", "schnell"
				players = playerSelection.getPlayers();
				winningScore = (players.size() - 1) * 10;
				iconManager.setPlayers(players);
				stage = CurvesRunning;
				showCountdown(countdown, window);
			}
			break;

		case CurvesRunning: //The actual game is running
			for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
				if (!players.at(i)->getCollided()) // Only move, if not collided
					players.at(i)->move();			
			}
			if (collidedCounter == players.size() || maxScore(players) >= winningScore) { //Determine, if the there is already a winner
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

			iconManager.onNewFrame();
			break;


		case GameIsOver: //Whole game is over or a new round has to start
			if (gameover.isNewGame()) { //Go back to start screen
				gameover.initiateNewGame();
				playerSelection.prepareNewGame();
				stage = SelectPlayers;
			}
			else {
				collidedCounter = 0;
				if (maxScore(players) >= winningScore) {
					stage = GameIsOver; //Game is either finished...
				}
				else {
					stage = CurvesRunning; //...or a new round should start
				}
				if (speedDynamization) { //Speed will be increased next round
					Player::dynamizationRate = Player::dynamizationRate + 0.1f;
				}
				for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
					
					players.at(i)->nextRound(playerSelection.dynamizeSpeed());
				}
				iconManager.reset();
			}
			break;
		}

		
		if (playerSelection.isFullscreen() && !fullscreen) { //Fullscreen
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
			iconManager.draw();
			for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
				players.at(i)->draw();
			}
			window->draw(leftBorder, 4, sf::Lines);
			break;

		case GameIsOver:
			if (maxScore(players) >= winningScore) {
				gameover.setPlayers(players);
				gameover.draw();
			}
			else {
				showCountdown(countdown, window);
			}
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


