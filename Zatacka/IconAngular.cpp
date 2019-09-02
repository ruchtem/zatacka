#include <SFML/Graphics.hpp>
#include <iostream>
#include "Icon.h"

using namespace std;
using namespace sf;

IconAngular::IconAngular(RenderWindow* window, Texture* texture) : Icon(window, texture) {

}

float IconAngular::alterAngle(float angle, Keyboard::Key leftKey, Keyboard::Key rightKey) {
	framesActive++;
	float newAngle = angle;

	if (framesSinceLastBend > 10) {
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