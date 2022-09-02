#include <iostream>
#include <algorithm>
#include "interactionManager.hpp"

ui::InteractionManager::InteractionManager() :
	interactions(), addInteractions(), deleteInteractions(), position(0, 0), block(false) {}

void ui::InteractionManager::addInteraction(IInteraction &interaction) {
	addInteractions.push_back(&interaction);
}

void ui::InteractionManager::deleteInteraction(IInteraction &interaction) {
	if(auto iterator = std::find(interactions.begin(), interactions.end(), &interaction); iterator != interactions.end())
		interactions.erase(iterator);
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
	
	if(!deleteInteractions.empty()) {
		ptrSort(deleteInteractions);
		for(auto& interaction : deleteInteractions) {
			interaction->finish(mousePosition);
		}
		deleteInteractions.clear();
	}
	
	if(!addInteractions.empty()) {
		ptrSort(addInteractions);
		for(auto& interaction : addInteractions) {
			interaction->start(mousePosition);
			interactions.push_back(interaction);
		}
	}
	
	if(!addInteractions.empty()) {
		ptrSort(interactions);
		addInteractions.clear();
	}
	
	for(auto interaction : interactions) {
		interaction->update(mousePosition);
	}
}
