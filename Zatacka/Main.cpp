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

	//RenderWindow window(VideoMode::getDesktopMode(), "Achtung - die Kurve!", Style::Fullscreen);
	RenderWindow window(VideoMode(800, 600), "Achtung - die Kurve!");
	window.setFramerateLimit(60);

	GameStages stage = SelectPlayers;

	PlayerSelection playerSelection = PlayerSelection(&window, &font);
	vector<Player*> players;

	// main loop
	while (window.isOpen())		
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();

			if (stage == SelectPlayers)
				playerSelection.processEvent(event);
		}

		if (playerSelection.isFinished()) {
			players = playerSelection.getPlayers();
			stage = CurvesRunning;
		}
		

		// Draw everything
		window.clear();

		if (stage == SelectPlayers)
			playerSelection.draw();
		else if (stage == CurvesRunning) {
			for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
				players.at(i)->move();
				players.at(i)->draw(&window);
			}
		}
			


		//if (player != NULL)
			//window.draw(player->getDot());
		//	player->draw(&window);

		window.display();
	}

	//delete player; player = NULL;

	return 0;
}


