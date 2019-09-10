#include <SFML/Graphics.hpp>
#include <iostream>
#include "Icon.h"

using namespace std;
using namespace sf;

IconSwitch::IconSwitch(RenderWindow* window, Texture* texture) : Icon(window, texture) { }

void IconSwitch::alterKeys(Keyboard::Key* leftKey, Keyboard::Key* rightKey) {
	cout << "IconSwitch frames to live " << framesToLive << endl;
	framesToLive--;

	if (!switched) {
		switched = true;
		// Store everything to be able to restore
		originalLeftKeyPtr = leftKey;
		originalRightKeyPtr = rightKey;
		originalLeftKey = *leftKey;
		originalRightKey = *rightKey;

		*leftKey = originalRightKey;
		*rightKey = originalLeftKey;
	}

	// Restore
	if (framesToLive == 0) {
		*originalLeftKeyPtr = originalLeftKey;
		*originalRightKeyPtr = originalRightKey;
	}
}

UpdateType IconSwitch::getUpdateType() {
	return IncreaseTime;
}

Icon* IconSwitch::copy() {
	return new IconSwitch(*this);
}
