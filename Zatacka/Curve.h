#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Curve {
private:
	Color color;
	string userName;
	int speed = 10;
	Keyboard::Key leftKey;
	Keyboard::Key rightKey;

	Vector2f position;
	vector<Vector2f> pastPositions;

public:
	const int MIN_RADIUS = 10;
	const int HOLE_DISTANCE = 10;

	Curve(const Color color, const string username);

	void setKeys(Keyboard::Key leftKey, Keyboard::Key rightKey);

	void move();
};