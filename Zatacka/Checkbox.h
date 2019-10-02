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
	Checkbox();
	Checkbox(String optionName, bool checked, Vector2f position, Font* font, RenderWindow* window);
	inline bool isChecked() { return this->checked; }
	inline void setChecked(bool checked) { this->checked = checked; }
	void check();
	FloatRect getGlobalBounds();
	void draw();
};

