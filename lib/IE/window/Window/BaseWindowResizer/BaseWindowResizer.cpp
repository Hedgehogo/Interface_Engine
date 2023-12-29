#include "BaseWindowResizer.hpp"

#include "../Window.hpp"

namespace ie {
	void BaseWindowResizer::set_window(Window& window) {
		BaseWindowResizer::window_ = &window;
	}
}