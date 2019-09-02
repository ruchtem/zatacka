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
	int framesToLive = 200;
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
	virtual void alterKeyBlock(int* framesToBlock) { }
	virtual void alterKeys(Keyboard::Key* leftKey, Keyboard::Key* rightKey) { }
	virtual void alterAngle(float* angle) { }
	virtual void alterSpeed(float* speed) { }
	void update(int framesToLive);
};

class IconAngular : public Icon {
private:
	int framesSinceLastBend = 100;	// Necessary to have no have two key strokes in almost same frame
public:
	virtual string getType() { return "angular"; }
	IconAngular(RenderWindow* window, Texture* texture);
	virtual void alterAngle(float* angle);
	virtual void alterKeyBlock(int* framesToBlock);
};

class IconSwitch : public Icon {
private:
	Keyboard::Key originalLeftKey = Keyboard::Key::Unknown;
	Keyboard::Key originalRightKey = Keyboard::Key::Unknown;
	Keyboard::Key* originalLeftKeyPtr = NULL;
	Keyboard::Key* originalRightKeyPtr = NULL;
	bool switched = false;
public:
	virtual string getType() { return "switch"; }
	IconSwitch(RenderWindow* window, Texture* texture);
	virtual void alterKeys(Keyboard::Key* leftKey, Keyboard::Key* rightKey);
};