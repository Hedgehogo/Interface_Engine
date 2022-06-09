#include <iostream>
#include "interactionManager.h"

ui::InteractionManager::InteractionManager(sf::RenderWindow &window) :
	window(window), interactions(), addInteractions(), deleteInteractions(), position(0, 0), block(false) {}

void ui::InteractionManager::addInteraction(IInteraction &interaction) {
	interactions.push_back(&interaction);
	addInteractions.push_back(&interaction);
}

void ui::InteractionManager::deleteInteraction(IInteraction &interaction) {
	for(unsigned i = 0; i < interactions.size(); ++i) {
		if(interactions[i] == &interaction) {
			interactions.erase(interactions.cbegin() + i);
			break;
		}
	}
	deleteInteractions.push_back(&interaction);
}

void ui::InteractionManager::clear() {
	for(auto& interaction : interactions) {
		interaction->finish(position);
	}
	interactions.clear();
}

bool ui::InteractionManager::blocked() {
	return block;
}

sf::Vector2i ui::InteractionManager::getPosition() {
	return position;
}

void ui::InteractionManager::update() {
	position = sf::Mouse::getPosition(window);
	for(auto& interaction : deleteInteractions) {
		interaction->finish(position);
	}
	deleteInteractions.clear();
	for(auto& interaction : addInteractions) {
		interaction->start(position);
	}
	addInteractions.clear();
	block = false;
	for(auto& interaction : interactions) {
		if(interaction->update(position)) {
			block = true;
		}
	}
}
