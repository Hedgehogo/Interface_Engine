
#include <algorithm>
#include "InteractionManager.hpp"

namespace ie {
	InteractionManager::InteractionManager() :
		interactions_(), add_interactions_(), delete_interactions_(), position_(0, 0), block_(false) {
	}
	
	size_t InteractionManager::size() {
		return interactions_.size();
	}
	
	IInteraction& InteractionManager::get(size_t index) {
		return *interactions_.at(index);
	}
	
	void InteractionManager::add_interaction(IInteraction& interaction) {
		add_interactions_.push_back(&interaction);
	}
	
	void InteractionManager::delete_interaction(IInteraction& interaction) {
		if(auto iterator = std::find(interactions_.begin(), interactions_.end(), &interaction); iterator != interactions_.end())
			interactions_.erase(iterator);
		delete_interactions_.push_back(&interaction);
	}
	
	void InteractionManager::clear() {
		for(auto& interaction: interactions_) {
			interaction->finish(position_);
		}
		interactions_.clear();
	}
	
	bool InteractionManager::is_blocked() const {
		return std::any_of(this->interactions_.begin(), this->interactions_.end(), [](IInteraction* interaction) {
			return interaction->is_blocked();
		});
	}
	
	void InteractionManager::update(sf::Vector2i mouse_position) {
		position_ = mouse_position;
		
		if(!delete_interactions_.empty()) {
			ptr_sort(delete_interactions_);
			for(auto& interaction: delete_interactions_) {
				interaction->finish(mouse_position);
			}
			delete_interactions_.clear();
		}
		
		if(!add_interactions_.empty()) {
			ptr_sort(add_interactions_);
			for(auto& interaction: add_interactions_) {
				interaction->start(mouse_position);
				interactions_.push_back(interaction);
			}
		}
		
		if(!add_interactions_.empty()) {
			ptr_sort(interactions_);
			add_interactions_.clear();
		}
		
		for(auto interaction: interactions_) {
			interaction->update(mouse_position);
		}
	}
}
