#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Player {
private:
	Color color;
	string name;
	float speed = 1;
	Keyboard::Key leftKey;
	Keyboard::Key rightKey;

	// The dot to be moved
	CircleShape curveDot;
	

	Vector2f position;
	float angle;	// Measured in radians
	vector<Vector2f> pastPositions;
	VertexArray curve;

public:
	const float MIN_RADIUS = 0.02;
	const int HOLE_DISTANCE = 10;
	const float PI = 3.14159265358979f;

	Player(const Color color, const string username);

	void setKeys(Keyboard::Key leftKey, Keyboard::Key rightKey);

	void move();
	void draw(RenderWindow* window);

	CircleShape getDot() { return curveDot; }
	VertexArray getCurve() { return curve; }
};