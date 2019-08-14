#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayerSelection.h"

using namespace std;
using namespace sf;

PlayerSelection::PlayerSelection() {

	if (!font.loadFromFile("resources/arial.ttf"))	// Necessary to render text
		throw exception("Could not load font!");

	headline.setFont(font);
	headline.setString("Bitte die Tasten auswählen");
	headline.setCharacterSize(24);
	headline.setFillColor(Color::Red);
	headline.setStyle(Text::Bold);
	headline.setPosition(xOffset + 300.f, yOffset);

	float textDistance = 40;
	float playersOffset = yOffset + 10;
	int characterSize = 24;

	for (int i = 0; i < 8; ++i) {
		playerNames[i].setString(names[i]);
		playerNames[i].setFillColor(colors[i]);
		playerNames[i].setFont(font);
		playerNames[i].setCharacterSize(characterSize);
		playerNames[i].setStyle(Text::Bold);
		playerNames[i].setPosition(xOffset, playersOffset + i * textDistance);
	}

}

void PlayerSelection::processEvent(Event event, RenderWindow* window) {
	Vector2f mousePosition = Vector2f(Mouse::getPosition((*window)));
	currentSelection = -1;

	// Show bounding box when mouse hovering over player name
	for (int i = 0; i < 8; ++i) {
		if (playerNames[i].getGlobalBounds().contains(mousePosition)) {
			currentSelection = i;
		}	
	}
	if (currentSelection >= 0) {
		FloatRect bounding = playerNames[currentSelection].getGlobalBounds();

		selectionRect = RectangleShape(sf::Vector2f(bounding.width + 2*selectionSpace, bounding.height + 2*selectionSpace));
		selectionRect.setFillColor(Color::Transparent);
		selectionRect.setOutlineThickness(2.f);
		selectionRect.setOutlineColor(sf::Color(100, 100, 100));
		selectionRect.setPosition(bounding.left - selectionSpace, bounding.top - selectionSpace);
	}
}

void PlayerSelection::draw(RenderWindow* window) {
	window->draw(headline);
	
	for (int i = 0; i < 8; ++i) {
		window->draw(playerNames[i]);
	}

	if (currentSelection >= 0)
		window->draw(selectionRect);
}