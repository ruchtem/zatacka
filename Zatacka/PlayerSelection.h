#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace std;
using namespace sf;

class PlayerSelection {
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

	Player* players[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
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

	void registerPlayerSelection(const Event event);
	void registerKeySelections(const Event event);
	int determineHoverSelection();
	void prepareSelectionDrawing();
	void registerStartClicked(const Event event);
	void registerFullscreenClicked(const Event event);

public:

	PlayerSelection(RenderWindow* window, Font* font);

	void processEvent(const Event event);

	bool isFinished();
	bool isFullscreen();
	vector<Player*> getPlayers();

	void draw();
};