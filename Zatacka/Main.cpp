#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

using namespace std;
using namespace sf;

int main()
{
	Font font;		// Necessary to render text
	if (!font.loadFromFile("resources/arial.ttf"))
		cout << "Could not load font!" << endl;
	
	

	RenderWindow window(VideoMode(800, 600), "Achtung - die Kurve!");
	vector<Keyboard::Key> keysPressed;



	// Key slection window
	Text headline;
	headline.setFont(font);
	headline.setString("Bitte die Tasten ausw�hlen");
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




	// Display which keys were selected
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


	

	// The dot to be moved
	CircleShape shape(10.f);
	shape.setFillColor(Color::Green);
	shape.setPosition(50.f, 50.f);



	// main loop
	while (window.isOpen())		
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			
			// Save key selection
			if (event.type == Event::KeyPressed) {
				keysPressed.push_back(event.key.code);
			}
		}

		// Move the dot using the previously selected keys
		if (keysPressed.size() >= 2) {
			Vector2f currentPosition = shape.getPosition();
			if (Keyboard::isKeyPressed(keysPressed.at(0))) {
				// left key is pressed -> move dot to bottom
				shape.setPosition(currentPosition.x + 1, currentPosition.y);
			}
			else if (Keyboard::isKeyPressed(keysPressed.at(1))) {
				// right key is pressed -> move dot to right
				shape.setPosition(currentPosition.x, currentPosition.y + 1);
			}
		}
		
		// Draw everything
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


