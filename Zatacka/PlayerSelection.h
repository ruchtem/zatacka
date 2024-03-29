#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Checkbox.h"
#include "SpeedChooser.h"

using namespace std;
using namespace sf;

class PlayerSelection {
private:
	const string names[8] = { //Every possible player name
		"Greenly", 
		"Red Rat", 
		"Greydon", 
		"Purple Fish", 
		"Blueband", 
		"Yellomingo", 
		"Cyanus", 
		"Whitey" 
	};

	//Colors of the players
	const Color colors[8] = { 
		Color::Green, 
		Color::Red, 
		Color(150, 150, 150), 
		Color::Magenta,
		Color::Blue, 
		Color::Yellow, 
		Color::Cyan, 
		Color::White };

	Player* players[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL}; //Maximum of 8 players
	RenderWindow* window;
	
	const float xOffset = .02f;	// percentages of window size
	const float yOffset = .02f;
	const float selectionSpace = .07f;
	const float textSize = .05f;
	const float playerNamesOffset = .1f;

	Font* font;		// Necessary to render text

	Text headline;
	Text startButton;
	Text fullscreen;
	Text playerNames[8];
	RectangleShape selectionRect;

	Text selectedKeys[8][2];

	SpeedChooser* speedChooser;
	Checkbox* dynamizationCheckbox;

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
	void registerSpeedDynamizationClicked(const Event event);
	void registerSpeedChooserClicked(const Event event);

public:

	PlayerSelection(RenderWindow* window, Font* font);
	~PlayerSelection();
	void init();

	void processEvent(const Event event);

	bool isFinished();
	bool dynamizeSpeed();
	bool shouldMakeFullscreen();
	void isFullscreenToggled(bool isFullscreen);
	vector<Player*> getPlayers();

	void draw();

	void prepareNewGame();

	float getStartSpeed();
};