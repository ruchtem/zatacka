#include <SFML/Graphics.hpp>
#include <iostream>
#include "Icon.h"

using namespace std;
using namespace sf;

IconSlower::IconSlower(RenderWindow* window, Texture* texture) : Icon(window, texture) { }

//slow down speed
void IconSlower::alterSpeed(float* speed, float* angle) {
	framesToLive--;
	(*speed) -= DECREASE_SPEED;
	(*angle) -= DECREASE_MIN_ANGLE;
}

//same icon increases intensity
UpdateType IconSlower::getUpdateType() {
	return Additive;
}

Icon* IconSlower::copy() {
	return new IconSlower(*this);
}
