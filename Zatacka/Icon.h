#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

// How the player moves should be affected  if an already active icon is collected again
enum UpdateType {
	IncreaseTime = 0,
	Additive = 1
};

class Icon {
protected:
	RenderWindow* window;
	Texture* texture;
	Sprite icon;
	bool forCollector;
	int framesDisplayed = 0;
	int framesToLive = 200;
	const float PI = 3.14159265358979f;
	const float MIN_RADIUS = 0.02f;
	const float SCALING_FACTOR = 1.f / 32.f;
	const int ICON_SIZE = 25;
	const int ICON_FREE_BORDER = 30;

public:
	Icon(RenderWindow* window, Texture* texture);
	// Shallow copys are fine, heap objects (texture, window) are managed outside of this class.
	void draw();
	int getFramesDisplayed();
	int getFramesToLive();
	bool contains(Vector2f position);
	bool isForCollector();
	bool isActive();
	virtual UpdateType getUpdateType();
	virtual string getType() { return "icon"; }
	virtual void alterKeyBlock(int* framesToBlock) { }
	virtual void alterKeys(Keyboard::Key* leftKey, Keyboard::Key* rightKey) { }
	virtual void alterAngle(float* angle) { }
	virtual void alterSpeed(float* speed, float* angle) { }
	void update(int framesToLive);
	virtual Icon* copy();
};

class IconAngular : public Icon {
private:
	int framesSinceLastBend = 100;	// Necessary to have no have two key strokes in almost same frame
public:
	virtual UpdateType getUpdateType();
	virtual string getType() { return "angular"; }
	IconAngular(RenderWindow* window, Texture* texture);
	virtual void alterAngle(float* angle);
	virtual void alterKeyBlock(int* framesToBlock);
	virtual Icon* copy();
};

class IconSwitch : public Icon {
private:
	Keyboard::Key originalLeftKey = Keyboard::Key::Unknown;
	Keyboard::Key originalRightKey = Keyboard::Key::Unknown;
	Keyboard::Key* originalLeftKeyPtr = NULL;
	Keyboard::Key* originalRightKeyPtr = NULL;
	bool switched = false;
public:
	virtual UpdateType getUpdateType();
	virtual string getType() { return "switch"; }
	IconSwitch(RenderWindow* window, Texture* texture);
	virtual void alterKeys(Keyboard::Key* leftKey, Keyboard::Key* rightKey);
	virtual Icon* copy();
};

class IconFaster : public Icon {
private:
	const float INCREASE_SPEED = 0.5f;
	const float INCREASE_MIN_ANGLE = 0.01f;
public:
	virtual UpdateType getUpdateType();
	virtual string getType() { return "faster"; }
	IconFaster(RenderWindow* window, Texture* texture);
	virtual Icon* copy();
	virtual void alterSpeed(float* speed, float* angle);
};

class IconSlower : public Icon {
private:
	const float DECREASE_SPEED = 0.5f;
	const float DECREASE_MIN_ANGLE = 0.01f;
public:
	virtual UpdateType getUpdateType();
	virtual string getType() { return "slower"; }
	IconSlower(RenderWindow* window, Texture* texture);
	virtual Icon* copy();
	virtual void alterSpeed(float* speed, float* angle);
};