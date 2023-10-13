#include "BaseWindowResizer.hpp"

#include "../Window.hpp"

namespace ie {
	void BaseWindowResizer::setWindow(Window& window) {
		BaseWindowResizer::window = &window;
	}
}