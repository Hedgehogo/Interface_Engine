
#include <algorithm>
#include "InteractionManager.hpp"

namespace ie {
	InteractionManager::InteractionManager() :
		interactions_(), add_interactions_(), delete_interactions_(), block_(false) {
	}
	
	auto InteractionManager::size() -> size_t {
		return interactions_.size();
	}
	
	auto InteractionManager::get(size_t index) -> IInteraction& {
		return *interactions_.at(index);
	}
	
	auto InteractionManager::add_interaction(IInteraction& interaction) -> void {
		add_interactions_.push_back(&interaction);
	}
	
	auto InteractionManager::delete_interaction(IInteraction& interaction) -> void {
		if(auto iterator = std::find(interactions_.begin(), interactions_.end(), &interaction); iterator != interactions_.end()) {
			interactions_.erase(iterator);
		}
		delete_interactions_.push_back(&interaction);
	}
	
	auto InteractionManager::clear() -> void {
		for(auto& interaction: interactions_) {
			interaction->finish();
		}
		interactions_.clear();
	}
	
	auto InteractionManager::is_blocked() const -> bool {
		return std::any_of(this->interactions_.begin(), this->interactions_.end(), [](IInteraction* interaction) {
			return interaction->is_prioritised();
		});
	}
	
	auto InteractionManager::handle_event(Event event) -> bool {
		bool result{false};
		for(auto iter = interactions_.begin(); iter != interactions_.end(); ++iter) {
			if((*iter)->handle_event(event)) {
				result = true;
				break;
			}
		}
		return result;
	}
	
	auto InteractionManager::update() -> void {
		if(!delete_interactions_.empty()) {
			ptr_sort(delete_interactions_);
			for(auto& interaction: delete_interactions_) {
				interaction->finish();
			}
			delete_interactions_.clear();
		}
		
		if(!add_interactions_.empty()) {
			ptr_sort(add_interactions_);
			for(auto& interaction: add_interactions_) {
				interaction->start();
				interactions_.push_back(interaction);
			}
		}
		
		if(!add_interactions_.empty()) {
			ptr_sort(interactions_);
			add_interactions_.clear();
		}
		
		for(auto interaction: interactions_) {
			interaction->update();
		}
	}
}
