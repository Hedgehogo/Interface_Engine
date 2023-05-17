#include "iWindowResizer.hpp"

#include "../window.hpp"

namespace ui {
	void IWindowResizer::setWindow(Window* window) {
		IWindowResizer::window = window;
	}
}