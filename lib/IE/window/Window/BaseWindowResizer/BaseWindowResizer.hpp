#pragma once

#include <SFML/System/Vector2.hpp>
#include "IE/interaction/IInteraction/IInteraction.hpp"

namespace ie {
	class Window;
	
	class BaseWindowResizer {
	public:
		virtual auto set_window(Window& window) -> void;
		
		virtual auto update(sf::Vector2i mouse_position) -> bool = 0;
		
		virtual ~BaseWindowResizer() = default;
	
	protected:
		Window* window_;
	};
}