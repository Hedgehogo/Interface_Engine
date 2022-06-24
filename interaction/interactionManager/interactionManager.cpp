#include <iostream>
#include "interactionManager.h"

ui::InteractionManager::InteractionManager() :
	interactions(), addInteractions(), deleteInteractions(), position(0, 0), block(false) {}

void ui::InteractionManager::addInteraction(IInteraction &interaction) {
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

bool ui::InteractionManager::isBlocked() {
	for(auto& interaction : interactions) {
		if(interaction->isBlocked()) {
			return true;
		}
	}
	return false;
}

void ui::InteractionManager::update(sf::Vector2i mousePosition) {
	position = mousePosition;
	for(auto& interaction : deleteInteractions) {
		interaction->finish(mousePosition);
	}
	deleteInteractions.clear();
	for(auto& interaction : addInteractions) {
		interaction->start(mousePosition);
        interactions.push_back(interaction);
	}
	addInteractions.clear();
	for(auto interaction : interactions) {
		interaction->update(mousePosition);
	}
}
