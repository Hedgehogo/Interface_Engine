
#include <algorithm>
#include "InteractionManager.hpp"

namespace ie {
	InteractionManager::InteractionManager() :
		interactions(), add_interactions(), delete_interactions(), position(0, 0), block(false) {
	}
	
	std::size_t InteractionManager::size() {
		return interactions.size();
	}
	
	IInteraction& InteractionManager::get(std::size_t index) {
		return *interactions.at(index);
	}
	
	void InteractionManager::add_interaction(IInteraction& interaction) {
		add_interactions.push_back(&interaction);
	}
	
	void InteractionManager::delete_interaction(IInteraction& interaction) {
		if(auto iterator = std::find(interactions.begin(), interactions.end(), &interaction); iterator != interactions.end())
			interactions.erase(iterator);
		delete_interactions.push_back(&interaction);
	}
	
	void InteractionManager::clear() {
		for(auto& interaction: interactions) {
			interaction->finish(position);
		}
		interactions.clear();
	}
	
	bool InteractionManager::is_blocked() const {
		return std::any_of(this->interactions.begin(), this->interactions.end(), [](IInteraction* interaction) {
			return interaction->is_blocked();
		});
	}
	
	void InteractionManager::update(sf::Vector2i mouse_position) {
		position = mouse_position;
		
		if(!delete_interactions.empty()) {
			ptr_sort(delete_interactions);
			for(auto& interaction: delete_interactions) {
				interaction->finish(mouse_position);
			}
			delete_interactions.clear();
		}
		
		if(!add_interactions.empty()) {
			ptr_sort(add_interactions);
			for(auto& interaction: add_interactions) {
				interaction->start(mouse_position);
				interactions.push_back(interaction);
			}
		}
		
		if(!add_interactions.empty()) {
			ptr_sort(interactions);
			add_interactions.clear();
		}
		
		for(auto interaction: interactions) {
			interaction->update(mouse_position);
		}
	}
}
