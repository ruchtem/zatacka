#include <SFML/Graphics.hpp>
#include "Curve.h"

using namespace std;
using namespace sf;


Curve::Curve(const Color color, const string userName) {
	this->color = color;
	this->userName = userName;

	// Initialize random starting position and direction
}

void Curve::move() {
	// Check if either left or right key is pressed

	// If not move straight

	// Update position
	pastPositions.push_back(position);
}
