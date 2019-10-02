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
	VertexArray curve;
	vector<Vector2f> curveArray;
	vector<CircleShape> circleCurve;

	const float xOffset = 20;
	const float yOffset = 20;

	vector<Icon*> consumedIcons;
	int numFramesToBlockKeyInput = 0;

	float textDistance = 40;
	float playersOffset = yOffset;
	int characterSize = 24;

	bool isCollided;

	const float PI = 3.14159265358979f;
	const float MIN_RADIUS = 0.06f;
	const float STD_SPEED = 2;

public:
	const int HOLE_DISTANCE = 10;

	Player(RenderWindow* window, Font* font, const Color color, const string username, const int rank);

	inline void setScore(int score) { this->score = score; }
	int getScore() { return score; }

	void setLeftKey(Keyboard::Key key);
	void setRightKey(Keyboard::Key key);
	bool isLeftKeySet();
	bool areBothKeysSet();
	void resetKeys();

	void move();
	void draw();

	void addConsumedIcon(Icon* icon);
	void setFramesToBlockKeyInput(int numFrames); //to implement

	bool collision(Image image, vector<Player*> players, sf::Vector2u windowSize);
	Vector2f getPosition();

	CircleShape getDot() { return curveDot; }

	VertexArray getCurve() { return curve; }
	vector<Vector2f> getCurveArray() { return curveArray; }
	bool getCollided() { return isCollided; }
	void setCollided(bool collision) { isCollided = collision; }
	Color getColor() { return color; }
	float getAngle() { return angle; }
	String getName() { return name; }
	
	void nextRound(Vector2u windowSize);
};