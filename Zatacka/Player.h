#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Player {
private:
	Color color;
	string name;
	int speed = 10;
	Keyboard::Key leftKey;
	Keyboard::Key rightKey;

	Vector2f position;
	vector<Vector2f> pastPositions;

public:
	const int MIN_RADIUS = 10;
	const int HOLE_DISTANCE = 10;

	Player(const Color color, const string username);

	void setKeys(Keyboard::Key leftKey, Keyboard::Key rightKey);

	void move();
};