#include "UpdateManager.hpp"

namespace ie {
	size_t UpdateManager::size() {
		return updatable_.size();
	}
	
	IUpdatable& UpdateManager::get(size_t index) {
		return *updatable_.at(index);
	}
	
	void UpdateManager::add(IUpdatable& updatable) {
		this->updatable_.push_back(&updatable);
	}
	
	void UpdateManager::clear() {
		updatable_.clear();
	}
	
	void UpdateManager::update() {
		for(auto& updatable: updatable_) {
			updatable->update();
		}
	}
}