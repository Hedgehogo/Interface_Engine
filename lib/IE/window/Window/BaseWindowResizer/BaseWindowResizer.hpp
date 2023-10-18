#pragma once

#include <SFML/System/Vector2.hpp>
#include "IE/interaction/IInteraction/IInteraction.hpp"

namespace ie {
	class Window;
	
	class BaseWindowResizer {
	public:
		virtual void set_window(Window& window);
	
		virtual bool update(sf::Vector2i mouse_position) = 0;
	
		virtual ~BaseWindowResizer() = default;
		
	protected:
		Window* window;
	};
}