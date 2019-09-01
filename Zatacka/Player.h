#pragma once
#include <SFML/Graphics.hpp>
#include "IconAngular.h"

using namespace sf;
using namespace std;

class Player {
private:
	Color color;
	string name;
	float speed = 1;
	Keyboard::Key leftKey = Keyboard::Key::Unknown;
	Keyboard::Key rightKey = Keyboard::Key::Unknown;

	//score of 10 wins
	int score = 0;

	// The dot to be moved
	CircleShape curveDot;
	

	Vector2f position;
	float angle;	// Measured in radians
	vector<Vector2f> pastPositions;
	VertexArray curve;
	vector<Vector2f> curveArray;

	vector<IconAngular> consumedIcons;

	bool isCollided;

	const float PI = 3.14159265358979f;
	const float MIN_RADIUS = 0.02f;

public:
	const int HOLE_DISTANCE = 10;

	Player(const Color color, const string username);

	inline void setScore(int score) { this->score = score; }
	int getScore() { return score; }

	void setLeftKey(Keyboard::Key key);
	void setRightKey(Keyboard::Key key);
	bool isLeftKeySet();
	bool areBothKeysSet();
	void resetKeys();

	void move();
	void draw(RenderWindow* window);

	void addConsumedIcon(IconAngular icon);

	bool collision(Image image, vector<Player*> players, sf::Vector2u windowSize);

	CircleShape getDot() { return curveDot; }
	Vector2f getPosition() { return position; }
	VertexArray getCurve() { return curve; }
	vector<Vector2f> getCurveArray() { return curveArray; }
	bool getCollided() { return isCollided; }
	void setCollided(bool collision) { isCollided = collision; }
	
	void nextRound();
};