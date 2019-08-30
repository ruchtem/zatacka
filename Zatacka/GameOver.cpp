#include "GameOver.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

GameOver::GameOver(RenderWindow* window, Font* font, vector<Player*> players) {
	this->window = window;
	this->font = font;
	this->players = players;

	headline.setFont((*font));
	headline.setString("Wir haben einen Gewinner!");
	headline.setCharacterSize(24);
	headline.setFillColor(Color::Red);
	headline.setStyle(Text::Bold);
	headline.setPosition(xOffset + 300.f, yOffset);

	startButton.setFont((*font));
	startButton.setString("Neues Spiel"); //Muss noch implementiert werden
	startButton.setCharacterSize(30);
	startButton.setFillColor(Color::White);
	startButton.setStyle(Text::Bold);
	startButton.setPosition(xOffset + 400.f, yOffset + 500.f);


	float textDistance = 40;
	float playersOffset = yOffset + 50;
	int characterSize = 24;

	float leftKeyOffset = xOffset + 200;
	float rightKeyOffset = xOffset + 400;

	for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
		playerNames[i].setString(names[i] + " " + to_string(players.at(i)->getScore()));
		playerNames[i].setFillColor(colors[i]);
		playerNames[i].setFont((*font));
		playerNames[i].setCharacterSize(characterSize);
		playerNames[i].setStyle(Text::Bold);
		playerNames[i].setPosition(xOffset, playersOffset + i * textDistance);

	}
}


void GameOver::draw() {
	window->draw(headline);
	window->draw(startButton);
	window->draw(fullscreen);

	for (int i = 0; i < 8; ++i) {
		window->draw(playerNames[i]);
	}

	if (hoverSelection >= 0 || selectedPlayer >= 0)
		window->draw(selectionRect);
}
