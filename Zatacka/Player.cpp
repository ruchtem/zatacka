#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace std;
using namespace sf;


Player::Player(const Color color, const string name) {
	this->color = color;
	this->name = name;

	// Initialize random starting position and direction
}

void Player::move() {
	// Check if either left or right key is pressed

	// If not move straight

	// Update position
	pastPositions.push_back(position);
}
