#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "PlayerSelection.h"

using namespace std;
using namespace sf;

enum GameStages {
	SelectPlayers = 0,
	CurvesRunning = 1,
	GameOver = 2
};

int main()
{
	Font font;
	if (!font.loadFromFile("resources/arial.ttf"))	// Necessary to render text
		throw exception("Could not load font!");

	RenderWindow* window = new RenderWindow(VideoMode(800, 600), "Achtung - die Kurve!");
	window->setFramerateLimit(60);
	bool fullscreen = false;

	GameStages stage = SelectPlayers;

	PlayerSelection playerSelection = PlayerSelection(window, &font);
	vector<Player*> players;

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
		}


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
				players.at(i)->move();
			}
			break;

		case GameOver:
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
				players.at(i)->draw(window);
			}
			break;

		case GameOver:
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


