#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Icon {
protected:
	RenderWindow* window;
	Texture* texture;
	Sprite icon;
	bool forCollector;
	int framesDisplayed = 0;
	int framesActive = 0;
	float PI = 3.14159265358979f;
	float MIN_RADIUS = 0.02f;

public:
	Icon(RenderWindow* window, Texture* texture);
	void draw();
	int getFramesDisplayed();
	FloatRect getBounds();
	bool isForCollector();
	bool isActive();
	virtual float alterAngle(float angle, Keyboard::Key leftKey, Keyboard::Key rightKey);
	float alterSpeed(float speed);
};

class IconAngular : public Icon {
private:
	int framesSinceLastBend = 100;	// Necessary to have no have two key strokes in almost same frame
public:
	IconAngular(RenderWindow* window, Texture* texture);
	virtual float alterAngle(float angle, Keyboard::Key leftKey, Keyboard::Key rightKey);
};