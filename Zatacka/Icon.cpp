#include <SFML/Graphics.hpp>
#include <iostream>
#include "Icon.h"

using namespace std;
using namespace sf;

Icon::Icon(RenderWindow* window, Texture* texture) {
	this->window = window;
	this->texture = texture;

	icon.setTexture(*texture);

	// Determine randomly if for the collecting player or all others
	if (rand() % 2 == 0) {
		forCollector = false;
		icon.setColor(Color::Red);
	}
	else {
		forCollector = true;
		icon.setColor(Color::Green);
	}

	Vector2u windowSize = window->getSize();
	icon.setPosition(rand() % windowSize.x, rand() % windowSize.y);
}

int Icon::getFramesDisplayed() {
	return framesDisplayed;
}

void Icon::draw() {
	framesDisplayed++;
	window->draw(icon);
}

FloatRect Icon::getBounds() {
	return icon.getGlobalBounds();
}

bool Icon::isForCollector() {
	return forCollector;
}

bool Icon::isActive() {
	if (framesActive < 200)
		return true;
	else
		return false;
}

float Icon::alterAngle(float angle, Keyboard::Key leftKey, Keyboard::Key rightKey) {
	float newAngle = angle;
	if (Keyboard::isKeyPressed(leftKey)) {
		newAngle = fmod(angle - MIN_RADIUS, 2 * PI);		// Measure in radians
	}
	else if (Keyboard::isKeyPressed(rightKey)) {
		newAngle = fmod(angle + MIN_RADIUS, 2 * PI);
	}
	return newAngle;
}

float Icon::alterSpeed(float speed) { 
	return speed; 
}