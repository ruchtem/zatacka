#pragma once
#include <SFML/Graphics.hpp>
#include "Icon.h"

using namespace sf;
using namespace std;

class Player {
private:
	RenderWindow* window;
	Font* font;
	Color color;
	string name;
	int rank;
	Keyboard::Key leftKey = Keyboard::Key::Unknown;
	Keyboard::Key rightKey = Keyboard::Key::Unknown;

	//score of (playercount - 1)*10 wins wins
	int score = 0;

	// The dot to be moved
	CircleShape curveDot;
	
	Vector2f position;
	float angle;	// Measured in radians
	vector<Vector2f> pastPositions;
	vector<Vector2f> curveArray;
	vector<CircleShape> circleCurve;

	const float xOffset = 20;
	const float yOffset = 20;

	vector<Icon*> consumedIcons;
	int numFramesToBlockKeyInput = 0;
	int framesUntilGap = 0;
	int framesUntilLine = 0;

	float textDistance = 40;
	float playersOffset = yOffset;
	int characterSize = 24;

	bool isCollided;

	const float PI = 3.14159265358979f;
	const float MIN_RADIUS = 0.05f;
	const float STD_SPEED = 1.75f;
	const float MAX_SPEED = 3.5f;
	const float MAX_ANGLE = 0.1f;
	const int GAP_FRAMES = 5;
	const int LINE_FRAMES = 80;

public:
	Player(RenderWindow* window, Font* font, const Color color, const string username, const int rank);

	static float dynamizationRate;

	inline void setScore(int score) { this->score = score; }
	void setLeftKey(Keyboard::Key key);
	void setRightKey(Keyboard::Key key);
	bool isLeftKeySet();
	bool areBothKeysSet();
	void resetKeys();
	void move();
	void draw();
	void addConsumedIcon(Icon* icon);
	bool collision(Image image, vector<Player*> players, sf::Vector2u windowSize);
	void nextRound(bool dynamize);
	
	Vector2f getPosition();
	bool getCollided() { return isCollided; }
	void setCollided(bool collision) { isCollided = collision; }
	Color getColor() { return color; }
	String getName() { return name; }
	int getScore() { return score; }
	Keyboard::Key getLeftKey() { return leftKey; }
	
	
};