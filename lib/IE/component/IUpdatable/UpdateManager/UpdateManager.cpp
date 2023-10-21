#include "UpdateManager.hpp"

namespace ie {
	size_t UpdateManager::size() {
		return updatable.size();
	}
	
	IUpdatable& UpdateManager::get(size_t index) {
		return *updatable.at(index);
	}
	
	void UpdateManager::add(IUpdatable& updatable) {
		this->updatable.push_back(&updatable);
	}
	
	void UpdateManager::clear() {
		updatable.clear();
	}
	
	void UpdateManager::update() {
		for(auto& updatable: updatable) {
			updatable->update();
		}
	}
}