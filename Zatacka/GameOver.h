#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace std;
using namespace sf;

class GameOver {
private:
	vector<Player*> players;
	RenderWindow* window;

	const float xOffset = 20;
	const float yOffset = 20;
	const float selectionSpace = 4;

	Font* font;		// Necessary to render text

	Text headline;
	Text startButton;
	Text fullscreen;
	Text playerNames[8];
	RectangleShape selectionRect;


	bool newGame = false;

public:
	GameOver(RenderWindow* window, Font* font);

	void setPlayers(vector<Player*> players);

	void draw();

	bool isNewGame() { return newGame; }
	void initiateNewGame();

	void registerNewGameClicked(const Event event);
	void processEvent(const Event event);
};

