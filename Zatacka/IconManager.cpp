#include <SFML/Graphics.hpp>
#include <iostream>
#include "IconManager.h"
#include <map>
#include <iterator>

using namespace sf;
using namespace std;

IconManager::IconManager(RenderWindow* window) {
	this->window = window;

	// Necessary to do here because textures are shared resources.
	map<string, string>::iterator it;
	for (it = textureFileNames.begin(); it != textureFileNames.end(); it++) {
		if (!textureMap[it->first].loadFromFile(textureFileNames[it->first])) {
			throw exception("Could not load texture");
		}
		textureMap[it->first].setSmooth(true);
	}
}

Icon* IconManager::newRandomIcon() {
	map<string, Texture>::iterator it = textureMap.begin();
	advance(it, rand() % textureMap.size());

	if (it->first == "angular") {
		return new IconAngular(window, &(it->second));
	}
	if (it->first == "switch") {
		return new IconSwitch(window, &(it->second));
	}
	throw exception("Trying to create a new random item which is not defined.");
}

void IconManager::setPlayers(vector<Player*> players) {
	this->players = players;
}

void IconManager::onNewFrame() {
	frameCount++;
	
	// Check if a player collected an item
	// Restriction: Process only one icon collection per frame (the second one is processed in the
	// proceeding frame anyways as the player is still within bounds).
	int iconCollected = -1;
	for (vector<Icon*>::size_type j = 0; j < displayedIcons.size(); ++j) {
		for (vector<Player*>::size_type i = 0; i < players.size(); ++i) {
			if (displayedIcons.at(j)->contains(players.at(i)->getPosition())) {
				// player i collected an icon! Now, whom does it affect?
				if (displayedIcons.at(j)->isForCollector()) {
					players.at(i)->addConsumedIcon(displayedIcons.at(j));
				}
				else {
					for (vector<Player*>::size_type k = 0; k < players.size(); ++k) {
						// Copies for all other players, cause they take care of it individually
						if (k != i)
							players.at(k)->addConsumedIcon(displayedIcons.at(j)->copy());
					}
					// We have to clear up the original now cause we copied
					delete displayedIcons.at(j); displayedIcons.at(j) = NULL;
				}
				iconCollected = j;
				break;
			}
		}
	}
	if (iconCollected >= 0)
		displayedIcons.erase(displayedIcons.begin() + iconCollected);

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
		if (rand() % ICON_FREQUENCY == 0) {	// New Icon all ICON_FREQUENCY frames
			displayedIcons.push_back(newRandomIcon());
		}
	}
}

void IconManager::reset() {
	frameCount = 0;
	for (vector<Icon*>::size_type i = 0; i < displayedIcons.size(); ++i) {
		delete displayedIcons.at(i); displayedIcons.at(i) = NULL;
	}
	displayedIcons.clear();
}

void IconManager::draw() {
	for (vector<Icon*>::size_type i = 0; i < displayedIcons.size(); ++i) {
		displayedIcons.at(i)->draw();
	}
}