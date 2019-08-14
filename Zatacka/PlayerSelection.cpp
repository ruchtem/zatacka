#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayerSelection.h"

using namespace std;
using namespace sf;

PlayerSelection::PlayerSelection() {

	if (!font.loadFromFile("resources/arial.ttf"))	// Necessary to render text
		throw exception("Could not load font!");

	float textDistance = 60;
	float playersOffset = yOffset + 10;
	int characterSize = 24;

	headline.setFont(font);
	headline.setString("Bitte die Tasten auswählen");
	headline.setCharacterSize(24);
	headline.setFillColor(Color::Red);
	headline.setStyle(Text::Bold);
	headline.setPosition(xOffset + 300.f, yOffset);

	player0.setString(names[0]);
	player0.setFillColor(colors[0]);
	player0.setFont(font);
	player0.setCharacterSize(characterSize);
	player0.setStyle(Text::Bold);
	player0.setPosition(xOffset, playersOffset + 0 * textDistance);

	player1.setString(names[1]);
	player1.setFillColor(colors[1]);
	player1.setFont(font);
	player1.setCharacterSize(characterSize);
	player1.setStyle(Text::Bold);
	player1.setPosition(xOffset, playersOffset + 1 * textDistance);
	
	player2.setString(names[2]);
	player2.setFillColor(colors[2]);
	player2.setFont(font);
	player2.setCharacterSize(characterSize);
	player2.setStyle(Text::Bold);
	player2.setPosition(xOffset, playersOffset + 2 * textDistance);

	player3.setString(names[3]);
	player3.setFillColor(colors[3]);
	player3.setFont(font);
	player3.setCharacterSize(characterSize);
	player3.setStyle(Text::Bold);
	player3.setPosition(xOffset, playersOffset + 3 * textDistance);

	player4.setString(names[4]);
	player4.setFillColor(colors[4]);
	player4.setFont(font);
	player4.setCharacterSize(characterSize);
	player4.setStyle(Text::Bold);
	player4.setPosition(xOffset, playersOffset + 4 * textDistance);

	player5.setString(names[5]);
	player5.setFillColor(colors[5]);
	player5.setFont(font);
	player5.setCharacterSize(characterSize);
	player5.setStyle(Text::Bold);
	player5.setPosition(xOffset, playersOffset + 5 * textDistance);

	player6.setString(names[6]);
	player6.setFillColor(colors[6]);
	player6.setFont(font);
	player6.setCharacterSize(characterSize);
	player6.setStyle(Text::Bold);
	player6.setPosition(xOffset, playersOffset + 6 * textDistance);

	player7.setString(names[7]);
	player7.setFillColor(colors[7]);
	player7.setFont(font);
	player7.setCharacterSize(characterSize);
	player7.setStyle(Text::Bold);
	player7.setPosition(xOffset, playersOffset + 7 * textDistance);
}

void PlayerSelection::draw(RenderWindow* window) {

	window->draw(headline);
	
	window->draw(player0);
	window->draw(player1);
	window->draw(player2);
	window->draw(player3);
	window->draw(player4);
	window->draw(player5);
	window->draw(player6);
	window->draw(player7);
}