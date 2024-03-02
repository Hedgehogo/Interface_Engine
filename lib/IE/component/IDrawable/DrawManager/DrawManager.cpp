#include "DrawManager.hpp"

namespace ie {
	auto DrawManager::add(IDrawable& drawable) -> void {
		drawables_.push_back(&drawable);
	}
	
	auto DrawManager::clear() -> void {
		drawables_.clear();
	}
	
	auto DrawManager::draw() -> void {
		for(auto& drawable: drawables_) {
			drawable->draw();
		}
	}
	
	auto DrawManager::size() -> size_t {
		return drawables_.size();
	}
	
	auto DrawManager::get(size_t index) -> IDrawable& {
		return *drawables_.at(index);
	}
}