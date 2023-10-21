#include "DrawManager.hpp"

namespace ie {
	void DrawManager::add(IDrawable& drawable) {
		drawables.push_back(&drawable);
	}
	
	void DrawManager::clear() {
		drawables.clear();
	}
	
	void DrawManager::draw() {
		for(auto& drawable: drawables) {
			drawable->draw();
		}
	}
	
	size_t DrawManager::size() {
		return drawables.size();
	}
	
	IDrawable& DrawManager::get(size_t index) {
		return *drawables.at(index);
	}
}