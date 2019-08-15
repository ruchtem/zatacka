#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "PlayerSelection.h"

using namespace std;
using namespace sf;

int main()
{
	
	
	

	//RenderWindow window(VideoMode::getDesktopMode(), "Achtung - die Kurve!", Style::Fullscreen);
	RenderWindow window(VideoMode(800, 600), "Achtung - die Kurve!");
	vector<Keyboard::Key> keysPressed;

	// Player names: greebly, redrat, greydon, purplefish, blueband
	PlayerSelection* playerSelection = new PlayerSelection(&window);



	// Display which keys were selected
	/*
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
	leftKey2.setPosition(200.f, 50.f);*/





	bool created = false;
	Player* player = NULL;

	// main loop
	while (window.isOpen())		
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
			
			// Save key selection
			if (event.type == Event::KeyPressed) {
				keysPressed.push_back(event.key.code);
			}

			playerSelection->processEvent(event);
		}

		if (!created && keysPressed.size() == 2) {
			player = new Player(Color::Red, "test");
			//player->setKeys(keysPressed.at(0), keysPressed.at(1));
			created = true;
		}
		
		if (player != NULL)
			player->move();

		// Draw everything
		window.clear();

		playerSelection->draw();

		/*
		for (vector<Keyboard::Key>::size_type i = 0; i < keysPressed.size(); ++i) {
			if (i == 0) {
				leftKey1.setString(to_string(keysPressed.at(i)));
				window.draw(leftKey1);
			}
			if (i == 1) {
				leftKey2.setString(to_string(keysPressed.at(i)));
				window.draw(leftKey2);
			}
		}*/

		if (player != NULL)
			//window.draw(player->getDot());
			player->draw(&window);

		window.display();
	}

	delete player; player = NULL;

	return 0;
}


