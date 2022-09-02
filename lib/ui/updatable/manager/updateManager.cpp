#include "updateManager.hpp"

namespace ui {
	void UpdateManager::add(IUpdatable &updatable) {
		updatables.push_back(&updatable);
	}
	
	void UpdateManager::clear() {
		updatables.clear();
	}
	
	void UpdateManager::update() {
		for(auto &updatable: updatables) {
			updatable->update();
		}
	}
}