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

	Font font;		// Necessary to render text

	Text headline;
	Text player0;
	Text player1;
	Text player2;
	Text player3;
	Text player4;
	Text player5;
	Text player6;
	Text player7;

public:

	PlayerSelection();

	void draw(RenderWindow* window);
};