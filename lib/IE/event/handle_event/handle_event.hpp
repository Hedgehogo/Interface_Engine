#pragma once

#include <SFML/Window/Event.hpp>

namespace ie {
	auto handle_event(sf::Event event) -> void;
	
	auto clear_event() -> void;
}