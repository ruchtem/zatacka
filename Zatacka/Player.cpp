#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "Player.h"

using namespace std;
using namespace sf;


Player::Player(const Color color, const string name) {
	this->color = color;
	this->name = name;

	// Initialize random starting position and angle
	position = Vector2f(400, 400);
	angle = 0;

	curveDot = CircleShape(3.f);
	curveDot.setFillColor(color);
	curveDot.setPosition(position);
}

void Player::setKeys(Keyboard::Key leftKey, Keyboard::Key rightKey) {
	this->leftKey = leftKey;
	this->rightKey = rightKey;
}

void Player::move() {
	// Change the angle when a relevant key is pressed
	if (Keyboard::isKeyPressed(leftKey)) {
		angle = fmod(angle - MIN_RADIUS, 2 * PI);		// Measure in radians
	}
	else if (Keyboard::isKeyPressed(rightKey)) {
		angle = fmod(angle + MIN_RADIUS, 2 * PI);
	}
	else {
		// We move straight, no need to change the angle
	}
	
	// New position based on speed and angle
	float x = position.x + speed * cos(angle);
	float y = position.y + speed * sin(angle);

	// Update position
	pastPositions.push_back(position);
	position = Vector2f(x, y);

	cout << x  << "  " << y << endl;

	curveDot.setPosition(position);
}

void Player::draw(RenderWindow* window) {
	for (vector<Vector2f>::size_type i = 0; i < pastPositions.size(); ++i) {
		CircleShape dot(3.f);
		dot.setFillColor(color);
		dot.setPosition(pastPositions.at(i));
		window->draw(dot);
	}
}

