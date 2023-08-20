#include "baseWindowResizer.hpp"

#include "../window.hpp"

namespace ui {
	void BaseWindowResizer::setWindow(Window& window) {
		BaseWindowResizer::window = &window;
	}
}