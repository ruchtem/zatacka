#include <SFML/Graphics.hpp>
#include <iostream>
#include "Icon.h"

using namespace std;
using namespace sf;

IconAngular::IconAngular(RenderWindow* window, Texture* texture) : Icon(window, texture) { }

void IconAngular::alterAngle(float* angle) {
	framesToLive--;
	*angle = .5f * PI;		// right angle
}

void IconAngular::alterKeyBlock(int* framesToBlock) {
	*framesToBlock = 10;
}

Icon* IconAngular::copy() {
	return new IconAngular(*this);
}

