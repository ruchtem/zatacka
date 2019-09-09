#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Icon.h"

using namespace sf;
using namespace std;

class IconManager {
private:
	RenderWindow* window;
	vector<Player*> players;
	int frameCount = 0;
	const int ICONFREE_START_FRAMES = 10;	// The number of frames until the first icon appears
	const int ICON_FREQUENCY = 50;			// The frequency in which new icons appear
	const unsigned int MAX_ICONS = 10;		// Max number of items which can appear at the same time
	vector<Icon*> displayedIcons;

	map<string, string> textureFileNames = {
		{"angular", "resources\\angular.png" },
		{"switch", "resources\\switch-keys.png" },
		{"faster", "resources\\faster.png"}
		//{"slower", "resources\\slower.png"}
	};
	map<string, Texture> textureMap;

	Icon* newRandomIcon();

public:
	IconManager(RenderWindow* window);
	void setPlayers(vector<Player*> players);
	void reset();
	void onNewFrame();
	void draw();
};