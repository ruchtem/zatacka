#include <SFML/Graphics.hpp>
#include <iostream>
#include "Icon.h"

using namespace std;
using namespace sf;

IconFaster::IconFaster(RenderWindow* window, Texture* texture) : Icon(window, texture) { }


//increase speed
void IconFaster::alterSpeed(float* speed, float* angle) {
	framesToLive--;
	(*speed) += INCREASE_SPEED;
	(*angle) += INCREASE_MIN_ANGLE;
}

//same icon increases intensity
UpdateType IconFaster::getUpdateType() {
	return Additive;
}

Icon* IconFaster::copy() {
	return new IconFaster(*this);
}
