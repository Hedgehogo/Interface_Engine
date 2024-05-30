#include "IMovePanelInteraction.hpp"

namespace ie {
	auto IMovePanelInteraction::start(sf::Vector2i mouse_position) -> void {
		if(get_at_start()) {
			move(mouse_position);
		}
	}
	
	auto IMovePanelInteraction::handle_event(Event event) -> bool {
		return false;
	}
	
	auto IMovePanelInteraction::update(sf::Vector2i mouse_position) -> void {
		if(!get_at_start()) {
			move(mouse_position);
		}
	}
	
	auto IMovePanelInteraction::finish(sf::Vector2i) -> void {
	}
}