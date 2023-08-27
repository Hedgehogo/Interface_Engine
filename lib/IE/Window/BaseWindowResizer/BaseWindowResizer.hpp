#pragma once

#include <SFML/System/Vector2.hpp>
#include "IE/Interaction/IInteraction/IInteraction.hpp"

namespace ie {
	class Window;
	
	class BaseWindowResizer {
	public:
		virtual void setWindow(Window& window);
	
		virtual bool update(sf::Vector2i mousePosition) = 0;
	
		virtual ~BaseWindowResizer() = default;
		
	protected:
		Window* window;
	};
}