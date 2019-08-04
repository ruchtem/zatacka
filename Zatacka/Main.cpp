#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

using namespace std;
using namespace sf;

int main()
{
	Font font;
	if (!font.loadFromFile("resources/arial.ttf"))
	{
		cout << "Could not load font!" << endl;
	}
	// Show key selecting menu
	RenderWindow window(VideoMode(800, 600), "Achtung - die Kurve!");


	// Key slection window
	Text headline;
	headline.setFont(font);
	headline.setString("Bitte die Tasten auswählen");
	headline.setCharacterSize(24);
	headline.setFillColor(Color::Red);
	headline.setStyle(Text::Bold);
	headline.setPosition(300.f, 10.f);

	Text greenly;
	greenly.setFont(font);
	greenly.setString("Greenly");
	greenly.setCharacterSize(24);
	greenly.setFillColor(Color::Green);
	greenly.setStyle(Text::Bold);
	greenly.setPosition(10.f, 50.f);

	Text redrat;
	redrat.setFont(font);
	redrat.setString("Red Rat");
	redrat.setCharacterSize(24);
	redrat.setFillColor(Color::Red);
	redrat.setStyle(Text::Bold);
	redrat.setPosition(10.f, 90.f);



	// Register key strokes as events. Remember wich key was pressed.
	Text leftKey1;
	leftKey1.setFont(font);
	leftKey1.setCharacterSize(24);
	leftKey1.setFillColor(Color::Green);
	leftKey1.setStyle(Text::Bold);
	leftKey1.setPosition(150.f, 50.f);

	Text leftKey2;
	leftKey2.setFont(font);
	leftKey2.setCharacterSize(24);
	leftKey2.setFillColor(Color::Green);
	leftKey2.setStyle(Text::Bold);
	leftKey2.setPosition(200.f, 50.f);


	vector<Keyboard::Key> keysPressed;

	// Start the game

	CircleShape shape(10.f);
	shape.setFillColor(Color::Green);
	shape.setPosition(50.f, 50.f);

	while (window.isOpen())		// main loop
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			
			if (event.type == Event::KeyPressed) {
				keysPressed.push_back(event.key.code);
			}
		}

		// This can be used later in the gameplay
		if (keysPressed.size() >= 2) {
			Vector2f currentPosition = shape.getPosition();
			if (Keyboard::isKeyPressed(keysPressed.at(0))) {
				// left key is pressed:
				shape.setPosition(currentPosition.x + 1, currentPosition.y);
			}
			else if (Keyboard::isKeyPressed(keysPressed.at(1))) {
				shape.setPosition(currentPosition.x, currentPosition.y + 1);
			}
		}
		

		window.clear();
		window.draw(headline);
		window.draw(greenly);
		window.draw(redrat);

		for (vector<Keyboard::Key>::size_type i = 0; i < keysPressed.size(); ++i) {
			if (i == 0) {
				leftKey1.setString(to_string(keysPressed.at(i)));
				window.draw(leftKey1);
			}
			if (i == 1) {
				leftKey2.setString(to_string(keysPressed.at(i)));
				window.draw(leftKey2);
			}
		}
			
		window.draw(shape);
		window.display();
	}

	return 0;
}


