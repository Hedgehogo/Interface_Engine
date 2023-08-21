#include "BaseWindowResizer.hpp"

#include "../Window.hpp"

namespace ui {
	void BaseWindowResizer::setWindow(Window& window) {
		BaseWindowResizer::window = &window;
	}
}