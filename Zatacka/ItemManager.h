#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Icon.h"

using namespace sf;
using namespace std;

class ItemManager {
private:
	RenderWindow* window;
	vector<Player*> players;
	int frameCount = 0;
	const int ICONFREE_START_FRAMES = 10;
	const int NUM_ICON_TYPES = 2;
	const unsigned int MAX_ICONS = 10;
	vector<Icon*> displayedIcons;
	Texture texture;

	Icon* newRandomIcon();

public:
	ItemManager(RenderWindow* window);
	void setPlayers(vector<Player*> players);
	void reset();
	void onNewFrame();
	void draw();
};