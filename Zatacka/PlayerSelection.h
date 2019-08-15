#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace std;
using namespace sf;

class PlayerSelection {
private:
	string names[8] = { "Greenly", "Red Rat", "Greydon", "Purple Fish", "Blueband", "Yellomingo", "Cyanus", "Whitey" };
	Color colors[8] = { Color::Green, Color::Red, Color(150, 150, 150), Color::Magenta, 
		                Color::Blue, Color::Yellow, Color::Cyan, Color::White };

	Player* players[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
	RenderWindow* window;
	
	float xOffset = 20;
	float yOffset = 20;
	float selectionSpace = 4;

	Font font;		// Necessary to render text

	Text headline;
	Text playerNames[8];
	RectangleShape selectionRect;

	Text selectedKeys[8][2];

	bool isPlayerSelected = false;
	int hoverSelection = -1;	// Mouse not hovering over a player
	int selectedPlayer = -1;	// No player selected

	void registerPlayerSelection(Event event);
	void registerKeySelections(Event event);
	int determineHoverSelection();
	void prepareSelectionDrawing();

public:

	PlayerSelection(RenderWindow* window);

	void processEvent(Event event);

	void draw();
};