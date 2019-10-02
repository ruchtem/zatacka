#pragma once
#include <SFML/Graphics.hpp>
#include "Checkbox.h"

using namespace std;
using namespace sf;

class SpeedChooser {
private:
	RenderWindow* window;
	Vector2u windowSize;

	Checkbox *option1, *option2, *option3;

	const float Y_DISTANCE = 20.f;

public:
	SpeedChooser(String option1, String option2, String option3, Vector2f position, RenderWindow* window, Font *font);
	void check(Vector2f mousePosition);
	float getPrefferedSpeed();
	void draw();
};

