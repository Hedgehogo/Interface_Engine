
#include <algorithm>
#include "TriggerManager.hpp"

namespace ie {
	TriggerManager::TriggerManager() : triggers_() {
	}
	
	auto TriggerManager::size() -> size_t {
		return triggers_.size();
	}
	
	auto TriggerManager::add_prioritised(IPrioritisedTrigger& trigger) -> void {
		triggers_.push_back(&trigger);
	}
	
	auto TriggerManager::delete_prioritised(IPrioritisedTrigger& trigger) -> void {
		if(auto iter = std::find(triggers_.begin(), triggers_.end(), &trigger); iter != triggers_.end()) {
			triggers_.erase(iter);
		}
	}
	
	auto TriggerManager::clear() -> void {
		triggers_.clear();
	}
	
	auto TriggerManager::is_blocked() const -> bool {
		return !triggers_.empty();
	}
	
	auto TriggerManager::handle_event(Event event) -> bool {
		for(auto trigger: triggers_) {
			if(trigger->handle_event(event)) {
				return true;
			}
		}
		return false;
	}
}
