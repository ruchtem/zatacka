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
	int framesToLive = 2000;
	float PI = 3.14159265358979f;
	float MIN_RADIUS = 0.02f;

public:
	Icon(RenderWindow* window, Texture* texture);
	void draw();
	int getFramesDisplayed();
	int getFramesToLive();
	FloatRect getBounds();
	bool isForCollector();
	bool isActive();
	virtual string getType() { return "icon"; }
	virtual float alterAngle(float angle, Keyboard::Key leftKey, Keyboard::Key rightKey);
	virtual float alterSpeed(float speed);
	void update(int framesToLive);
};

class IconAngular : public Icon {
private:
	int framesSinceLastBend = 100;	// Necessary to have no have two key strokes in almost same frame
public:
	virtual string getType() { return "angular"; }
	IconAngular(RenderWindow* window, Texture* texture);
	virtual float alterAngle(float angle, Keyboard::Key leftKey, Keyboard::Key rightKey);
};

class IconSwitch : public Icon {
public:
	virtual string getType() { return "switch"; }
	IconSwitch(RenderWindow* window, Texture* texture);
	virtual float alterAngle(float angle, Keyboard::Key leftKey, Keyboard::Key rightKey);
};