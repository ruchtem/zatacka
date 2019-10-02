#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Checkbox {
private: 
	RenderWindow* window;
	Vector2u windowSize;

	Text optionName;
	RectangleShape checkRect;

	bool checked;

public:
	Checkbox(String optionName, Vector2f position, Font* font, RenderWindow* window);
	inline bool isChecked() { return this->checked; }
	void setChecked(bool checked);
	void check();
	FloatRect getGlobalBounds();
	void draw();
};

