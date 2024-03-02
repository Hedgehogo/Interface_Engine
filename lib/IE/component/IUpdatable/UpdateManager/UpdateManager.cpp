#include "UpdateManager.hpp"

namespace ie {
	auto UpdateManager::size() -> size_t {
		return updatable_.size();
	}
	
	auto UpdateManager::get(size_t index) -> IUpdatable& {
		return *updatable_.at(index);
	}
	
	auto UpdateManager::add(IUpdatable& updatable) -> void {
		this->updatable_.push_back(&updatable);
	}
	
	auto UpdateManager::clear() -> void {
		updatable_.clear();
	}
	
	auto UpdateManager::update() -> void {
		for(auto& updatable: updatable_) {
			updatable->update();
		}
	}
}