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

	curve = VertexArray(PrimitiveType::LineStrip);

	// Initialize random starting position
	float x = rand() % static_cast<int>(window->getSize().x - (window->getSize().x * .21f)) + (window->getSize().x * .14f);
	float y = rand() % static_cast<int>(window->getSize().y - window->getSize().y * .14f) + (window->getSize().y * .07f);
	position = Vector2f(x, y);
	angle = 0; //Starting with an angle of zero in the first round

	curveDot = CircleShape(4.f);
	curveDot.setFillColor(color);
	curveDot.setPosition(position);
	circleCurve.push_back(curveDot);
}

float Player::dynamizationRate = 1.0f;

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

void Player::resetKeys() { //Delete saved keys
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
		}
		else
			++i;
	}
	
	//Set angle and speed in every frame, to make sure there is no delay... 
	float angleChange = MIN_RADIUS  * dynamizationRate;
	float speedChange = STD_SPEED * dynamizationRate;
	if (speedChange > MAX_SPEED) {
		speedChange = MAX_SPEED;
		angleChange = MAX_ANGLE;
	}
	cout << speedChange;
	int blockChange = 0;
	
	//...if a player used an icon
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
	//draw the score of every player
	Text scoreText;
	scoreText.setString(to_string(score));
	scoreText.setFillColor(color);
	scoreText.setFont((*font));
	scoreText.setCharacterSize(characterSize);
	scoreText.setStyle(Text::Bold);
	scoreText.setPosition(xOffset, playersOffset + rank * textDistance);

	//Draw the curve
	window->draw(curve);
	window->draw(curveDot);
	for (vector<CircleShape>::size_type i = 0; i < circleCurve.size(); i++) {
		window->draw(circleCurve.at(i));
	}
	//Draw score
	window->draw(scoreText);
}

Vector2f Player::getPosition() {
	return this->position;
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

bool Player::collision(Image image, vector<Player*> players, Vector2u windowSize) { //Player collision mehtod
	for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
		if (!players.at(i)->curveArray.empty()) { //Curve shouldn't be empty
			Vector2f position = curveArray.back();

			float xUnit = windowSize.x / 100.f; //Fit the collision detection to the screen size
			float yUnit = windowSize.y / 100.f;
			float xCollisionCorrection = 1.5f * xUnit;
			float yCollisionCorrection = 1.5f * yUnit;
			if (position.x + xCollisionCorrection * cos(angle) >= windowSize.x || 
					position.x + xCollisionCorrection * cos(angle) <= 0 || 
					position.y + yCollisionCorrection * sin(angle) >= windowSize.y || 
					position.y + yCollisionCorrection * sin(angle) <= 0) { //Is the player inside the screen?
				cout << "Collision";
				return true;
			}
			unsigned int x = static_cast<unsigned int>(position.x + yCollisionCorrection * cos(angle));
			unsigned int y = static_cast<unsigned int>(position.y + yCollisionCorrection * sin(angle));
			if (image.getPixel(x, y) != Color::Black) { //pixel perfect detection with position correction too reduce errors
				cout << "Collision";
				return true;
			}
		}
	}
	return false;
}

void Player::nextRound(bool dynamize) { //A round ended and a new one has to be prepared
	for (vector<Icon*>::size_type i = 0; i < consumedIcons.size(); ++i) {
		delete consumedIcons.at(i); consumedIcons.at(i) = NULL;
	}
	consumedIcons.clear();
	isCollided = false;
	curve.clear();
	curveArray.clear();
	circleCurve.clear();
	pastPositions.clear();
	float x = rand() % static_cast<int>(window->getSize().x - (window->getSize().x * .21f)) + (window->getSize().x * .14f);
	float y = rand() % static_cast<int>(window->getSize().y - window->getSize().y * .14f) + (window->getSize().y * .07f);
	position = Vector2f(x, y);
}

