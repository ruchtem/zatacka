#include "SpeedChooser.h"

SpeedChooser::SpeedChooser(String option1Name, String option2Name, String option3Name, Vector2f position, RenderWindow* window, Font* font) {
	this->window = window;
	this->windowSize = window->getSize();

	this->option1 = new Checkbox(option1Name, position, font, window);
	this->option2 = new Checkbox(option2Name, Vector2f(position.x, position.y + Y_DISTANCE + option1->getGlobalBounds().height), font, window);
	this->option3 = new Checkbox(option3Name, Vector2f(position.x, position.y + 2*Y_DISTANCE + option2->getGlobalBounds().height*2), font, window);
}

void SpeedChooser::check(Vector2f mousePosition) { //Check or uncheck the clicked checkbox. Only one box can be checked at the same time
	if (option1->getGlobalBounds().contains(mousePosition)) {
		option1->check();
		option2->setChecked(false);
		option3->setChecked(false);
	}
	else if (option2->getGlobalBounds().contains(mousePosition)) {
		option2->check();
		option1->setChecked(false);
		option3->setChecked(false);
	}
	else if (option3->getGlobalBounds().contains(mousePosition)) {
		option3->check();
		option1->setChecked(false);
		option2->setChecked(false);
	}
}

float SpeedChooser::getPrefferedSpeed() { //Return 0 (none) or 1, 2, 3 for the options
	if (option1->isChecked()) return 0.75;
	else if (option2->isChecked()) return 1;
	else if (option3->isChecked()) return 1.5;
	else return 1;
}

void SpeedChooser::draw() {
	option1->draw();
	option2->draw();
	option3->draw();
}
