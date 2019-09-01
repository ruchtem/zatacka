#include <SFML/Graphics.hpp>
#include <iostream>
#include "IconAngular.h"

using namespace std;
using namespace sf;

IconAngular::IconAngular(RenderWindow* window, Texture* texture) {
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

int IconAngular::getFramesDisplayed() {
	return framesDisplayed;
}

void IconAngular::draw() {
	framesDisplayed++;
	window->draw(icon);
}

FloatRect IconAngular::getBounds() {
	return icon.getGlobalBounds();
}

bool IconAngular::isForCollector() {
	return forCollector;
}

float IconAngular::alterAngle(float angle, Keyboard::Key leftKey, Keyboard::Key rightKey) {
	float newAngle = angle;

	if (framesSinceLastBend > 5) {
		framesSinceLastBend = 0;
		if (Keyboard::isKeyPressed(leftKey)) {
			newAngle = fmod(angle - .5f * PI, 2 * PI);		// Measure in radians
		}
		else if (Keyboard::isKeyPressed(rightKey)) {
			newAngle = fmod(angle + .5f * PI, 2 * PI);
		}
	}
	else {
		framesSinceLastBend++;
	}
	
	return newAngle;
}