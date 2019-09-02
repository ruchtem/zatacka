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
	position = Vector2f(rand() % 800, rand() % 600);
	angle = 0;

	curveDot = CircleShape(4.f);
	curveDot.setFillColor(color);
	curveDot.setPosition(position);
}

void Player::setLeftKey(Keyboard::Key key) {
	this->leftKey = key;
}

void Player::setRightKey(Keyboard::Key key) {
	this->rightKey = key;
}

bool Player::isLeftKeySet() {
	return leftKey != Keyboard::Key::Unknown;
}

bool Player::areBothKeysSet() {
	return leftKey != Keyboard::Key::Unknown && rightKey != Keyboard::Key::Unknown;
}

void Player::resetKeys() {
	leftKey = Keyboard::Key::Unknown;
	rightKey = Keyboard::Key::Unknown;
}

void Player::move() {
	
	if (consumedIcons.empty()) {
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
	}
	else {
		for (vector<Icon>::size_type i = 0; i < consumedIcons.size(); ++i) {
			if (consumedIcons.at(i)->isActive()) {
				speed = consumedIcons.at(i)->alterSpeed(speed);
				angle = consumedIcons.at(i)->alterAngle(angle, leftKey, rightKey);
			}
		}

		// Delete non-active items
		vector<Icon>::size_type i = 0;
		while (i < consumedIcons.size()) {
			if (!consumedIcons.at(i)->isActive()) {
				delete consumedIcons.at(i); consumedIcons.at(i) = NULL;
				consumedIcons.erase(consumedIcons.begin() + i);
				cout << "Player: " << name << " an asctive icon finished and is removed!" << endl;
			}
			else
				++i;
		}
	}
	
	// New position based on speed and angle
	float x = position.x + speed * cos(angle);
	float y = position.y + speed * sin(angle);
	
	// Update position
	position = Vector2f(x, y);


	curve.append(Vertex(Vector2f(x, y), color));
	curveArray.push_back(Vector2f(x, y));
	curveDot.setPosition(Vector2f(x - 2.f, y - 2.f));
}

void Player::draw(RenderWindow* window) {
	window->draw(curve);
	window->draw(curveDot);
}

void Player::addConsumedIcon(Icon* icon) {
	cout << "Player: " << name << " consumed an icon!" << endl;
	consumedIcons.push_back(icon);
}

bool Player::collision(Image image, vector<Player*> players, sf::Vector2u windowSize) {
	for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
		if (!players.at(i)->curveArray.empty()) {
			//cout << "curve Array not empty!";
			Vector2f point = curveArray.back();

			if (point.x >= windowSize.x || point.x <= 0 || point.y >= windowSize.y || point.y <= 0) {
				cout << "Collision";
				return true;
			}
			if (image.getPixel(point.x, point.y) == players.at(i)->color && color != players.at(i)->color) {
				//Curve2 contains Point of Curve1 -> Collision
				cout << "Collision";
				return true;
			}
		}
	}
	return false;
}

void Player::nextRound() {
	consumedIcons.clear();
	isCollided = false;
	curve.clear();
	curveArray.clear();
	pastPositions.clear();
	position = Vector2f(rand() % 800, rand() % 600);
}

