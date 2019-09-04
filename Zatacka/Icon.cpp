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

bool Icon::contains(Vector2f position) {
	return icon.getGlobalBounds().contains(position);
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

Icon* Icon::copy() {
	return new Icon(*this);
}