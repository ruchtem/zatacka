#include <SFML/Graphics.hpp>
#include <iostream>
#include "ItemManager.h"

using namespace sf;
using namespace std;

ItemManager::ItemManager(RenderWindow* window) {
	this->window = window;

	if (!texture.loadFromFile("resources\\angular-others.png")) {
		throw exception("Could not load texture");
	}
	texture.setSmooth(true);
}

void ItemManager::setPlayers(vector<Player*> players) {
	this->players = players;
}

void ItemManager::onNewFrame() {
	frameCount++;
	// Check if a player collected an item
	for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
		for (vector<IconAngular>::size_type j = 0; j < displayedItems.size(); ++j) {
			Player* p = players.at(i);
			if (displayedItems.at(j).getBounds().contains(p->getPosition())) {
				IconAngular icon = displayedItems.at(j);
				if (icon.isForCollector()) {
					players.at(i)->addConsumedIcon(icon);
				}
				else {
					for (vector<Player*>::size_type k = 0; k < players.size(); ++k) {
						if (k != i) {
							players.at(i)->addConsumedIcon(icon);
						}
					}
				}
				
			}
		}
	}


	// Remove old icon?
	vector<IconAngular>::size_type i = 0;
	while (i < displayedItems.size()) {
		if (displayedItems.at(i).getFramesDisplayed() > 500) {
			displayedItems.erase(displayedItems.begin() + i);
		}
		else {
			++i;
		}
	}
	
	// Add new Icon?
	if (frameCount > ITEMFREE_START_FRAMES && displayedItems.size() < MAX_ITEMS) {
		if (rand() % 50 == 0) {	// New Icon all 500 frames
			displayedItems.push_back(IconAngular(window, &texture));
		}
	}
}

void ItemManager::reset() {
	frameCount = 0;
	displayedItems.clear();
}

void ItemManager::draw() {
	for (vector<IconAngular>::size_type i = 0; i < displayedItems.size(); ++i) {
		displayedItems.at(i).draw();
	}
}