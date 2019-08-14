#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class PlayerSelection {
private:
	string names[8] = { "Greenly", "Red Rat", "Greydon", "Purple Fish", "Blueband", "Yellomingo", "Cyanus", "Whitey" };
	Color colors[8] = { Color::Green, Color::Red, Color(150, 150, 150), Color::Magenta, 
		                Color::Blue, Color::Yellow, Color::Cyan, Color::White };

	float xOffset = 0;
	float yOffset = 0;
	float selectionSpace = 4;

	Font font;		// Necessary to render text

	Text headline;
	Text playerNames[8];
	RectangleShape selectionRect;

	int currentSelection = -1;	// No player selected

public:

	PlayerSelection();

	void processEvent(Event event, RenderWindow* window);

	void draw(RenderWindow* window);
};