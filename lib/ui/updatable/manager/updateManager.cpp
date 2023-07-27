#include "updateManager.hpp"

namespace ui {
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