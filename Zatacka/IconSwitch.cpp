#include <SFML/Graphics.hpp>
#include <iostream>
#include "Icon.h"

using namespace std;
using namespace sf;

IconSwitch::IconSwitch(RenderWindow* window, Texture* texture) : Icon(window, texture) { }

float IconSwitch::alterAngle(float angle, Keyboard::Key leftKey, Keyboard::Key rightKey) {
	framesActive++;
	float newAngle = angle;
	if (Keyboard::isKeyPressed(rightKey)) {
		newAngle = fmod(angle - MIN_RADIUS, 2 * PI);		// Measure in radians
	}
	else if (Keyboard::isKeyPressed(leftKey)) {
		newAngle = fmod(angle + MIN_RADIUS, 2 * PI);
	}
	return newAngle;
}
