
#include <algorithm>
#include "InteractionManager.hpp"

namespace ie {
	InteractionManager::InteractionManager() : interactions_() {
	}
	
	auto InteractionManager::size() -> size_t {
		return interactions_.size();
	}
	
	auto InteractionManager::add_prioritised(IPrioritisedInteraction& interaction) -> void {
		interactions_.push_back(&interaction);
	}
	
	auto InteractionManager::delete_prioritised(IPrioritisedInteraction& interaction) -> void {
		if(auto iter = std::find(interactions_.begin(), interactions_.end(), &interaction); iter != interactions_.end()) {
			interactions_.erase(iter);
		}
	}
	
	auto InteractionManager::clear() -> void {
		interactions_.clear();
	}
	
	auto InteractionManager::is_blocked() const -> bool {
		return !interactions_.empty();
	}
	
	auto InteractionManager::handle_event(Event event) -> bool {
		for(auto interaction: interactions_) {
			if(interaction->handle_event(event)) {
				return true;
			}
		}
		return false;
	}
}
