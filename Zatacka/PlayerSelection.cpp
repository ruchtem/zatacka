#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayerSelection.h"

using namespace std;
using namespace sf;

// Display the approriate string for the selected key instead of the number
map<Keyboard::Key, string> KeyString = {
	{Keyboard::A, "A" },
	{Keyboard::B, "B" },
	{Keyboard::C, "C" },
	{Keyboard::D, "D" },
	{Keyboard::E, "E" },
	{Keyboard::F, "F" },
	{Keyboard::G, "G" },
	{Keyboard::H, "H" },
	{Keyboard::I, "I" },
	{Keyboard::J, "J" },
	{Keyboard::K, "K" },
	{Keyboard::L, "L" },
	{Keyboard::M, "M" },
	{Keyboard::N, "N" },
	{Keyboard::O, "O" },
	{Keyboard::P, "P" },
	{Keyboard::Q, "Q" },
	{Keyboard::R, "R" },
	{Keyboard::S, "S" },
	{Keyboard::T, "T" },
	{Keyboard::U, "U" },
	{Keyboard::V, "V" },
	{Keyboard::W, "W" },
	{Keyboard::X, "X" },
	{Keyboard::Y, "Y" },
	{Keyboard::Z, "Z" },
	{Keyboard::Num0, "0" },
	{Keyboard::Num1, "1" },
	{Keyboard::Num2, "2" },
	{Keyboard::Num3, "3" },
	{Keyboard::Num4, "4" },
	{Keyboard::Num5, "5" },
	{Keyboard::Num6, "6" },
	{Keyboard::Num7, "7" },
	{Keyboard::Num8, "8" },
	{Keyboard::Num9, "9" },
	{Keyboard::LControl, "left Control" },
	{Keyboard::LShift, "left Shift" },
	{Keyboard::LAlt, "left Alt" },
	{Keyboard::RControl, "right Control" },
	{Keyboard::RShift, "right Shift" },
	{Keyboard::RAlt, "right Alt" },
	{Keyboard::Menu, "Menu" },
	{Keyboard::LBracket, "[" },
	{Keyboard::RBracket, "]" },
	{Keyboard::Semicolon, ";" },
	{Keyboard::Comma, "," },
	{Keyboard::Period, "." },
	{Keyboard::Quote, "'" },
	{Keyboard::Slash, "/" },
	{Keyboard::Backslash, "\\" },
	{Keyboard::Tilde, "~" },
	{Keyboard::Equal, "=" },
	{Keyboard::Hyphen, "-"},
	{Keyboard::Space, "Space" },
	{Keyboard::Enter, "Enter"},
	{Keyboard::Backspace, "Backspace" },
	{Keyboard::Tab, "Tabulation" },
	{Keyboard::PageUp, "Page up" },
	{Keyboard::PageDown, "Page down" },
	{Keyboard::End, "End" },
	{Keyboard::Home, "Home" },
	{Keyboard::Insert, "Insert" },
	{Keyboard::Delete, "Delete" },
	{Keyboard::Add, "+" },
	{Keyboard::Subtract, "-"},
	{Keyboard::Multiply, "*" },
	{Keyboard::Divide, "/" },
	{Keyboard::Left, "Left arrow"},
	{Keyboard::Right, "Right arrow"},
	{Keyboard::Up, "Up arrow"},
	{Keyboard::Down, "Down arrow"},
	{Keyboard::Numpad0, "numpad 0" },
	{Keyboard::Numpad1, "numpad 1" },
	{Keyboard::Numpad2, "numpad 2" },
	{Keyboard::Numpad3, "numpad 3" },
	{Keyboard::Numpad4, "numpad 4" },
	{Keyboard::Numpad5, "numpad 5" },
	{Keyboard::Numpad6, "numpad 6" },
	{Keyboard::Numpad7, "numpad 7" },
	{Keyboard::Numpad8, "numpad 8" },
	{Keyboard::Numpad9, "numpad 9" },
	{Keyboard::F1, "F1" },
	{Keyboard::F2, "F2" },
	{Keyboard::F3, "F3" },
	{Keyboard::F4, "F4" },
	{Keyboard::F5, "F5" },
	{Keyboard::F6, "F6" },
	{Keyboard::F7, "F7" },
	{Keyboard::F8, "F8" },
	{Keyboard::F9, "F9" },
	{Keyboard::F10, "F10" },
	{Keyboard::F11, "F11" },
	{Keyboard::F12, "F12" },
	{Keyboard::F13, "F13" },
	{Keyboard::F14, "F14" },
	{Keyboard::F15, "F15" }								
};


PlayerSelection::PlayerSelection(RenderWindow* window) {
	this->window = window;

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

	float leftKeyOffset = xOffset + 200;
	float rightKeyOffset = xOffset + 400;

	for (int i = 0; i < 8; ++i) {
		playerNames[i].setString(names[i]);
		playerNames[i].setFillColor(colors[i]);
		playerNames[i].setFont(font);
		playerNames[i].setCharacterSize(characterSize);
		playerNames[i].setStyle(Text::Bold);
		playerNames[i].setPosition(xOffset, playersOffset + i * textDistance);

		for (int j = 0; j < 2; ++j) {
			selectedKeys[i][j].setFillColor(colors[i]);
			selectedKeys[i][j].setFont(font);
			selectedKeys[i][j].setCharacterSize(characterSize);
			selectedKeys[i][j].setStyle(Text::Bold);
		}

		selectedKeys[i][0].setPosition(leftKeyOffset, playersOffset + i * textDistance);
		selectedKeys[i][1].setPosition(rightKeyOffset, playersOffset + i * textDistance);
	}
}

void PlayerSelection::processEvent(Event event) {
	registerPlayerSelection(event);
	registerKeySelections(event);
}

void PlayerSelection::registerPlayerSelection(Event event) {
	hoverSelection = determineHoverSelection();

	// Check if player is selected by mouse click
	if (hoverSelection >= 0 && event.type == Event::MouseButtonPressed) {
		selectedPlayer = hoverSelection;
	}

	// Player unselected
	if (hoverSelection == -1 && event.type == Event::MouseButtonPressed) {
		selectedPlayer = -1;
	}

	prepareSelectionDrawing();
}

int PlayerSelection::determineHoverSelection() {
	Vector2f mousePosition = Vector2f(Mouse::getPosition((*window)));

	// Check if mouse is hovering over a player and if yes over which
	for (int i = 0; i < 8; ++i) {
		if (playerNames[i].getGlobalBounds().contains(mousePosition)) {
			return i;
		}
	}
	return -1;
}

void PlayerSelection::prepareSelectionDrawing() {
	if (selectedPlayer >= 0) {
		FloatRect textBounds = playerNames[selectedPlayer].getGlobalBounds();

		selectionRect = RectangleShape(sf::Vector2f(textBounds.width + 2 * selectionSpace, textBounds.height + 2 * selectionSpace));
		selectionRect.setFillColor(Color::Transparent);
		selectionRect.setOutlineThickness(3.f);
		selectionRect.setOutlineColor(sf::Color(150, 150, 150));
		selectionRect.setPosition(textBounds.left - selectionSpace, textBounds.top - selectionSpace);
	}
	else if (hoverSelection >= 0) {
		FloatRect textBounds = playerNames[hoverSelection].getGlobalBounds();

		selectionRect = RectangleShape(sf::Vector2f(textBounds.width + 2 * selectionSpace, textBounds.height + 2 * selectionSpace));
		selectionRect.setFillColor(Color::Transparent);
		selectionRect.setOutlineThickness(2.f);
		selectionRect.setOutlineColor(sf::Color(100, 100, 100));
		selectionRect.setPosition(textBounds.left - selectionSpace, textBounds.top - selectionSpace);
	}
}

void PlayerSelection::registerKeySelections(Event event) {
	if (selectedPlayer >= 0 && event.type == Event::KeyPressed) {
		if (players[selectedPlayer] == NULL) {
			players[selectedPlayer] = new Player(colors[selectedPlayer], names[selectedPlayer]);
		}

		// When we get a new key for a player with already set keys -> override both
		if (players[selectedPlayer]->areBothKeysSet()) {
			players[selectedPlayer]->resetKeys();
		}

		// Check if key is valid
		if (KeyString.count(event.key.code) == 0) {
			return;
		}

		if (!players[selectedPlayer]->isLeftKeySet()) {
			players[selectedPlayer]->setLeftKey(event.key.code);
			selectedKeys[selectedPlayer][0].setString(KeyString[event.key.code]);
		}
		else {
			players[selectedPlayer]->setRightKey(event.key.code);
			selectedKeys[selectedPlayer][1].setString(KeyString[event.key.code]);
		}
	}
}

void prepareKeySelectionDrawing() {

}

void PlayerSelection::draw() {
	window->draw(headline);
	
	for (int i = 0; i < 8; ++i) {
		window->draw(playerNames[i]);
		if (players[i] != NULL) {
			if (players[i]->isLeftKeySet()) {
				window->draw(selectedKeys[i][0]);
			}
			if (players[i]->areBothKeysSet()) {
				window->draw(selectedKeys[i][1]);
			}
		}
	}

	if (hoverSelection >= 0 || selectedPlayer >= 0)
		window->draw(selectionRect);
}