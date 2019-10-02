#include <SFML/Graphics.hpp>
#include <iostream>
#include "Icon.h"

using namespace std;
using namespace sf;

IconAngular::IconAngular(RenderWindow* window, Texture* texture) : Icon(window, texture) { }

//change turning angle
void IconAngular::alterAngle(float* angle) {
	framesToLive--;
	*angle = .5f * PI;		// right angle
}

//block input for frames
void IconAngular::alterKeyBlock(int* framesToBlock) {
	*framesToBlock = 10;
}

//same icon inreases time
UpdateType IconAngular::getUpdateType() {
	return IncreaseTime;
}

Icon* IconAngular::copy() {
	return new IconAngular(*this);
}

