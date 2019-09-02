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
	vector<Icon*>::size_type j = 0;
	while (j < displayedIcons.size()) {
		int items_consumed = 0;
		for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
			Player* p = players.at(i);
			if (displayedIcons.at(j)->getBounds().contains(p->getPosition())) {
				if (displayedIcons.at(j)->isForCollector()) {
					players.at(i)->addConsumedIcon(displayedIcons.at(j));
				}
				else {
					for (vector<Player*>::size_type k = 0; k < players.size(); ++k) {
						if (k != i) {
							players.at(i)->addConsumedIcon(displayedIcons.at(j));
						}
					}
				}
				items_consumed++;
				displayedIcons.erase(displayedIcons.begin() + j);
			}
		}
		if (items_consumed == 0) {
			j++;
		}
		
	}

	// Remove old icon?
	vector<Icon>::size_type i = 0;
	while (i < displayedIcons.size()) {
		if (displayedIcons.at(i)->getFramesDisplayed() > 500) {
			delete displayedIcons.at(i); displayedIcons.at(i) = NULL;
			displayedIcons.erase(displayedIcons.begin() + i);
		}
		else {
			++i;
		}
	}
	
	// Add new Icon?
	if (frameCount > ICONFREE_START_FRAMES && displayedIcons.size() < MAX_ICONS) {
		if (rand() % 50 == 0) {	// New Icon all 500 frames
			displayedIcons.push_back(new IconAngular(window, &texture));
		}
	}
}

void ItemManager::reset() {
	frameCount = 0;
	for (vector<Icon*>::size_type i = 0; i < displayedIcons.size(); ++i) {
		delete displayedIcons.at(i); displayedIcons.at(i) = NULL;
	}
	displayedIcons.clear();
}

void ItemManager::draw() {
	for (vector<Icon*>::size_type i = 0; i < displayedIcons.size(); ++i) {
		displayedIcons.at(i)->draw();
	}
}