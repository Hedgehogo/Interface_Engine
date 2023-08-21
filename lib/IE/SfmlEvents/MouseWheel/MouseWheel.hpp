#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

namespace ui {
	class MouseWheel {
	protected:
		static sf::Vector2f delta;
	
	public:
		static void setDelta(sf::Event::MouseWheelScrollEvent event);
		
		static void setDelta(sf::Vector2f delta);
		
		static sf::Vector2f getDelta();
		
		static void clear();
	};
}