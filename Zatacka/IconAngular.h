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
	float PI = 3.14159265358979f;
	float MIN_RADIUS = 0.02f;

public:
	IconAngular(RenderWindow* window, Texture* texture);
	void draw();
	int getFramesDisplayed();
	FloatRect getBounds();
	bool isForCollector();
	float alterAngle(float angle, Keyboard::Key leftKey, Keyboard::Key rightKey);
	float alterSpeed(float speed) { return speed; }
};