#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace std;
using namespace sf;

class GameOver {
private:
	const string names[8] = {
		"Greenly",
		"Red Rat",
		"Greydon",
		"Purple Fish",
		"Blueband",
		"Yellomingo",
		"Cyanus",
		"Whitey"
	};

	const Color colors[8] = {
		Color::Green,
		Color::Red,
		Color(150, 150, 150),
		Color::Magenta,
		Color::Blue,
		Color::Yellow,
		Color::Cyan,
		Color::White };

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

	Text selectedKeys[8][2];

	bool isPlayerSelected = false;
	int hoverSelection = -1;	// Mouse not hovering over a player
	int selectedPlayer = -1;	// No player selected

	bool playerSelectionFinished = false;
	bool fullscreenToggled = false;

public:

	GameOver(RenderWindow* window, Font* font, vector<Player*> players);

	void draw();
};

