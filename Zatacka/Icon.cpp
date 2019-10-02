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

	this->windowSize = window->getSize();
	icon.setPosition(rand() % (windowSize.x - windowSize.x / 100 * 17) + (windowSize.x / 100 * 14), rand() % (windowSize.y - windowSize.y / 100 * 13) + (windowSize.y / 100 * 10)); //Setting position with distance to window bounds
}

int Icon::getFramesDisplayed() {
	return framesDisplayed;
}

void Icon::draw() {
	framesDisplayed++;
	window->draw(icon);
}

bool Icon::contains(Vector2f position) { //test, if the player is collided with an icon
	float xUnit = windowSize.x / 100;
	float yUnit = windowSize.y / 100;
	float xCorrection = 1.5 * xUnit;
	float yCorrection = 1.5 * yUnit;

	float xLeft = icon.getGlobalBounds().left - xCorrection;
	float xRight = icon.getGlobalBounds().left + icon.getGlobalBounds().width + xCorrection;
	float yTop = icon.getGlobalBounds().top - yCorrection;
	float yBottom = icon.getGlobalBounds().top + icon.getGlobalBounds().height + yCorrection;
	return (position.x > xLeft && position.x < xRight && position.y > yTop && position.y < yBottom); //player is in bounds?
}

bool Icon::isForCollector() {
	return forCollector;
}

int Icon::getFramesToLive() {
	return framesToLive;
}

bool Icon::isActive() {
	if (framesToLive > 0)
		return true;
	else
		return false;
}

void Icon::update(int framesToLive) {
	this->framesToLive += framesToLive;
}

UpdateType Icon::getUpdateType() {
	return Additive;	// Should never been used.
}

Icon* Icon::copy() {
	return new Icon(*this);
}