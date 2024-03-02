#include "BaseWindowResizer.hpp"

#include "../Window.hpp"

namespace ie {
	auto BaseWindowResizer::set_window(Window& window) -> void {
		BaseWindowResizer::window_ = &window;
	}
}