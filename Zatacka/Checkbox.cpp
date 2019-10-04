#include "Checkbox.h"


Checkbox::Checkbox(String optionName, Vector2f position, Font* font, RenderWindow* window) {
	this->window = window;
	this->windowSize = window->getSize();
	this->optionName.setString(optionName);
	this->optionName.setCharacterSize(24);
	this->optionName.setFont(*font);
	this->optionName.setPosition(Vector2f(position.x + windowSize.x / 100 * 4, position.y)); //Text is placed behind the checkbox with 2% screen width distance

	checkRect = RectangleShape(Vector2f(windowSize.x * .03f, windowSize.x * .03f)); //Checkbox size scales to the size of the width of the game window
	checkRect.setFillColor(Color::Transparent);
	checkRect.setOutlineThickness(2.f);
	checkRect.setOutlineColor(Color(150, 150, 150));
	checkRect.setPosition(position);

	this->checked = false;
}

void Checkbox::setChecked(bool checked) {
	this->checked = checked;
	if (checked) {
		checkRect.setFillColor((sf::Color(150, 150, 150)));
	}
	else {
		checkRect.setFillColor(Color::Transparent);
	}
}

void Checkbox::check() {
	if (this->checked) {
		this->checked = false;
		checkRect.setFillColor(Color::Transparent);
	}
	else {
		this->checked = true;
		checkRect.setFillColor(sf::Color(150, 150, 150));
	}
}

void Checkbox::draw() {
	window->draw(optionName);
	window->draw(checkRect);
}

FloatRect Checkbox::getGlobalBounds() {
	return checkRect.getGlobalBounds();
}
