#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main()
{
	// Show key selecting menu
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	// -> Register key strokes as events. Remember wich key was pressed.

	// Start the game


	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Keyboard::Key pressedKey;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Event::KeyPressed)
				pressedKey = event.key.code;
				std::cout << pressedKey << endl;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			// left key is pressed: Change color to blue
			shape.setFillColor(sf::Color::Blue);
		}
		else {
			shape.setFillColor(sf::Color::Green);
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}


