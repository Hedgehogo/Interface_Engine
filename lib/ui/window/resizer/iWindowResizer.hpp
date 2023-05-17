#pragma once

#include <SFML/System/Vector2.hpp>
#include "ui/interaction/iInteraction/iInteraction.hpp"

namespace ui {
	class Window;
	
	class IWindowResizer{
	protected:
		Window* window;
		
	public:
		virtual void setWindow(Window* window);
	
		virtual bool update(sf::Vector2i mousePosition) = 0;
	};
	
}