#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "Player.h"

using namespace std;
using namespace sf;


Player::Player(const Color color, const string name) {
	this->color = color;
	this->name = name;

	//curve = VertexArray(PrimitiveType::TriangleStrip);
	curve = VertexArray(PrimitiveType::LineStrip);

	// Initialize random starting position and angle
	position = Vector2f(400, 400);
	angle = 0;

	curveDot = CircleShape(4.f);
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
	position = Vector2f(x, y);

	//cout << x  << "  " << y << "      " << pastPositions.size() << endl;

	curve.append(Vertex(Vector2f(x, y), color));
	curveDot.setPosition(Vector2f(x - 2.f, y - 2.f));
}

void Player::draw(RenderWindow* window) {
	


	window->draw(curve);
	window->draw(curveDot);
}

