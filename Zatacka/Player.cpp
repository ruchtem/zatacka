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
	circleCurve.push_back(curveDot);
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


	curve.append(Vertex(Vector2f(x, y), color));
	curveArray.push_back(Vector2f(x, y));
	curveDot.setPosition(Vector2f(x - 2.f, y - 2.f));
	circleCurve.push_back(curveDot);
}

void Player::draw(RenderWindow* window, Font* font, int i) {


	Text scoreText;
	scoreText.setString(to_string(score));
	scoreText.setFillColor(color);
	scoreText.setFont((*font));
	scoreText.setCharacterSize(characterSize);
	scoreText.setStyle(Text::Bold);
	scoreText.setPosition(xOffset, playersOffset + i * textDistance);

	window->draw(curve);
	window->draw(curveDot);

	for (vector<CircleShape>::size_type i = 0; i < circleCurve.size(); i++) {
		window->draw(circleCurve.at(i));
	}
	window->draw(scoreText);

}

bool Player::collision(Image image, vector<Player*> players, Vector2u windowSize) {
	for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
		if (!players.at(i)->curveArray.empty()) {
			//cout << "curve Array not empty!";
			Vector2f point = curveArray.back();

			if (point.x + 8 * cos(angle) >= windowSize.x || point.x + 8 * cos(angle) <= 0 || point.y + 8 * sin(angle) >= windowSize.y || point.y + 8 * sin(angle) <= 0) {
				cout << "Collision";
				return true;
			}
			if (image.getPixel(point.x + 8 * cos(angle), point.y + 8 * sin(angle)) != Color::Black) {
				//Curve2 contains Point of Curve1 -> Collision
				cout << "Collision";
				return true;
			}
		}
	}
	return false;
}

void Player::nextRound(Vector2u windowSize) {
	isCollided = false;
	curve.clear();
	curveArray.clear();
	circleCurve.clear();
	pastPositions.clear();
	position = Vector2f(rand() % (windowSize.x - windowSize.x / 100 * 7) + windowSize.x / 100 * 7, rand() % windowSize.y);
}

