#include "DrawManager.hpp"

namespace ie {
	void DrawManager::add(IDrawable& drawable) {
		drawables_.push_back(&drawable);
	}
	
	void DrawManager::clear() {
		drawables_.clear();
	}
	
	void DrawManager::draw() {
		for(auto& drawable: drawables_) {
			drawable->draw();
		}
	}
	
	size_t DrawManager::size() {
		return drawables_.size();
	}
	
	IDrawable& DrawManager::get(size_t index) {
		return *drawables_.at(index);
	}
}