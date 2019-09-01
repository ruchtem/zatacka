#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "IconAngular.h"

using namespace sf;
using namespace std;

class ItemManager {
private:
	RenderWindow* window;
	vector<Player*> players;
	int frameCount = 0;
	const int ITEMFREE_START_FRAMES = 10;
	const unsigned int MAX_ITEMS = 10;
	vector<IconAngular> displayedItems;
	Texture texture;

public:
	ItemManager(RenderWindow* window);
	void setPlayers(vector<Player*> players);
	void reset();
	void onNewFrame();
	void draw();
};