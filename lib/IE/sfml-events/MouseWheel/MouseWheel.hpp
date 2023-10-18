#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

namespace ie {
	class MouseWheel {
	protected:
		static sf::Vector2f delta;
	
	public:
		static void set_delta(sf::Event::MouseWheelScrollEvent event);
		
		static void set_delta(sf::Vector2f delta);
		
		static sf::Vector2f get_delta();
		
		static void clear();
	};
}