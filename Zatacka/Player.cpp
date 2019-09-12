#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "Player.h"

using namespace std;
using namespace sf;

Player::Player(RenderWindow* window, Font* font, const Color color, const string name, const int rank) {
	this->window = window;
	this->font = font;
	this->color = color;
	this->name = name;
	this->rank = rank;

	//curve = VertexArray(PrimitiveType::TriangleStrip);
	curve = VertexArray(PrimitiveType::LineStrip);

	// Initialize random starting position and angle
	position = Vector2f(rand() % window->getSize().x, rand() % window->getSize().y);
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
	
	// Delete non-active items
	vector<Icon>::size_type i = 0;
	while (i < consumedIcons.size()) {
		if (!consumedIcons.at(i)->isActive()) {
			delete consumedIcons.at(i); consumedIcons.at(i) = NULL;
			consumedIcons.erase(consumedIcons.begin() + i);
			cout << "Player: " << name << " an active icon finished and is removed!" << endl;
		}
		else
			++i;
	}

	//cout << "Player: " << name << " has " << consumedIcons.size() << " active icons" << endl;
	float angleChange = MIN_RADIUS;
	float speedChange = STD_SPEED;
	int blockChange = 0;
	
	for (vector<Icon*>::size_type i = 0; i < consumedIcons.size(); ++i) {
		if (consumedIcons.at(i)->isActive()) {
			consumedIcons.at(i)->alterSpeed(&speedChange, &angleChange);
			consumedIcons.at(i)->alterAngle(&angleChange);
			consumedIcons.at(i)->alterKeys(&leftKey, &rightKey);
			consumedIcons.at(i)->alterKeyBlock(&blockChange);
		}
	}

	// Change the angle when a relevant key is pressed
	// This can be modified by icons
	if (numFramesToBlockKeyInput == 0) {
		if (Keyboard::isKeyPressed(leftKey)) {
			angle = fmod(angle - angleChange, 2 * PI);		// Measure in radians
		}
		else if (Keyboard::isKeyPressed(rightKey)) {
			angle = fmod(angle + angleChange, 2 * PI);
		}
		else {
			// We move straight, no need to change the angle
		}

		numFramesToBlockKeyInput = blockChange;
	}
	else {
		numFramesToBlockKeyInput--;
	}

	// New position based on speed and angle
	float x = position.x + speedChange * cos(angle);
	float y = position.y + speedChange * sin(angle);
	
	// Update position
	position = Vector2f(x, y);

	curve.append(Vertex(Vector2f(x, y), color));
	curveArray.push_back(Vector2f(x, y));
	curveDot.setPosition(Vector2f(x - 2.f, y - 2.f));
	circleCurve.push_back(curveDot);
}

void Player::draw() {
	Text scoreText;
	scoreText.setString(to_string(score));
	scoreText.setFillColor(color);
	scoreText.setFont((*font));
	scoreText.setCharacterSize(characterSize);
	scoreText.setStyle(Text::Bold);
	scoreText.setPosition(xOffset, playersOffset + rank * textDistance);

	window->draw(curve);
	window->draw(curveDot);

	for (vector<CircleShape>::size_type i = 0; i < circleCurve.size(); i++) {
		window->draw(circleCurve.at(i));
	}
	window->draw(scoreText);
}

void Player::addConsumedIcon(Icon* icon) {
	cout << "Player: " << name << " consumed an icon!" << endl;
	if (consumedIcons.empty()) {
		consumedIcons.push_back(icon);
	}
	else {
		if (icon->getUpdateType() == IncreaseTime) {
			// Increase the time to live for the same kind of icon
			bool updated = false;
			for (vector<Icon*>::size_type i = 0; i < consumedIcons.size(); ++i) {
				if (consumedIcons.at(i)->getType() == icon->getType()) {
					consumedIcons.at(i)->update(icon->getFramesToLive());
					delete icon; icon = NULL;
					updated = true;
				}
			}
			if (!updated) {
				consumedIcons.push_back(icon);
			}
		}
		else if (icon->getUpdateType() == Additive) {
			// These kind of icons work additive
			consumedIcons.push_back(icon);
		}
		else {
			throw exception("Unknown update type for icon.");
		}
		
	}
	
	
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
	for (vector<Icon*>::size_type i = 0; i < consumedIcons.size(); ++i) {
		delete consumedIcons.at(i); consumedIcons.at(i) = NULL;
	}
	consumedIcons.clear();	// TODO Memory leak!
	isCollided = false;
	curve.clear();
	curveArray.clear();
	circleCurve.clear();
	pastPositions.clear();
	position = Vector2f(rand() % (windowSize.x - windowSize.x / 100 * 7) + windowSize.x / 100 * 7, rand() % windowSize.y);
}

