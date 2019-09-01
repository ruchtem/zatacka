#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class IconAngular {
private:
	RenderWindow* window;
	Texture* texture;
	Sprite icon;
	bool forCollector;
	int framesDisplayed = 0;
	int framesActive = 0;
	int framesSinceLastBend = 100;	// Necessary to have no have two key strokes in almost same frame
	float PI = 3.14159265358979f;
	float MIN_RADIUS = 0.02f;

public:
	IconAngular(RenderWindow* window, Texture* texture);
	void draw();
	int getFramesDisplayed();
	FloatRect getBounds();
	bool isForCollector();
	bool isActive();
	float alterAngle(float angle, Keyboard::Key leftKey, Keyboard::Key rightKey);
	float alterSpeed(float speed) { return speed; }
};