#include "drawManager.hpp"

namespace ui {
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
}