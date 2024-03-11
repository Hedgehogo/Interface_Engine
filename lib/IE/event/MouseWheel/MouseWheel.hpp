#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

namespace ie {
	class MouseWheel {
	protected:
		static sf::Vector2f delta_;
	
	public:
		static auto set_delta(sf::Event::MouseWheelScrollEvent event) -> void;
		
		static auto set_delta(sf::Vector2f delta) -> void;
		
		static auto get_delta() -> sf::Vector2f;
		
		static auto clear() -> void;
	};
}