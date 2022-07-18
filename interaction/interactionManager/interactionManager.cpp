#include <iostream>
#include "interactionManager.h"

ui::InteractionManager::InteractionManager() :
	interactions(), hidePanelInteractions(), addInteractions(), deleteInteractions(), position(0, 0), block(false) {}

void ui::InteractionManager::addInteraction(IInteraction &interaction) {
	if(interaction.getType() != InteractionType::hidePanel) {
		addInteractions.push_back(&interaction);
	} else {
		hidePanelInteractions.push_back(&interaction);
	}
}

void ui::InteractionManager::deleteInteraction(IInteraction &interaction) {
	if(auto iterator = std::find(interactions.begin(), interactions.end(), &interaction); iterator != interactions.end())
		interactions.erase(iterator);
	if(auto iterator = std::find(hidePanelInteractions.begin(), hidePanelInteractions.end(), &interaction); iterator != hidePanelInteractions.end())
		hidePanelInteractions.erase(iterator);
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
	for(auto interaction : hidePanelInteractions) {
		interaction->update(mousePosition);
	}
}
