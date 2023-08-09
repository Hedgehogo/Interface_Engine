#pragma once

#include <SFML/System/Vector2.hpp>
#include "ui/interaction/iInteraction/iInteraction.hpp"

namespace ui {
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