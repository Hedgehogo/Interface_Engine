
#include <algorithm>
#include "InteractionManager.hpp"

namespace ui {
	InteractionManager::InteractionManager() :
		interactions(), addInteractions(), deleteInteractions(), position(0, 0), block(false) {
	}
	
	std::size_t InteractionManager::size() {
		return interactions.size();
	}
	
	IInteraction& InteractionManager::get(std::size_t index) {
		return *interactions.at(index);
	}
	
	void InteractionManager::addInteraction(IInteraction& interaction) {
		addInteractions.push_back(&interaction);
	}
	
	void InteractionManager::deleteInteraction(IInteraction& interaction) {
		if(auto iterator = std::find(interactions.begin(), interactions.end(), &interaction); iterator != interactions.end())
			interactions.erase(iterator);
		deleteInteractions.push_back(&interaction);
	}
	
	void InteractionManager::clear() {
		for(auto& interaction: interactions) {
			interaction->finish(position);
		}
		interactions.clear();
	}
	
	bool InteractionManager::isBlocked() const {
		return std::any_of(this->interactions.begin(), this->interactions.end(), [](IInteraction* interaction) {
			return interaction->isBlocked();
		});
	}
	
	void InteractionManager::update(sf::Vector2i mousePosition) {
		position = mousePosition;
		
		if(!deleteInteractions.empty()) {
			ptrSort(deleteInteractions);
			for(auto& interaction: deleteInteractions) {
				interaction->finish(mousePosition);
			}
			deleteInteractions.clear();
		}
		
		if(!addInteractions.empty()) {
			ptrSort(addInteractions);
			for(auto& interaction: addInteractions) {
				interaction->start(mousePosition);
				interactions.push_back(interaction);
			}
		}
		
		if(!addInteractions.empty()) {
			ptrSort(interactions);
			addInteractions.clear();
		}
		
		for(auto interaction: interactions) {
			interaction->update(mousePosition);
		}
	}
}
