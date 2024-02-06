#include "IMovePanelInteraction.hpp"

namespace ie {
	void IMovePanelInteraction::start(sf::Vector2i mouse_position) {
		if(get_at_start())
			move(mouse_position);
	}
	
	void IMovePanelInteraction::update(sf::Vector2i mouse_position) {
		if(!get_at_start())
			move(mouse_position);
	}
	
	void IMovePanelInteraction::finish(sf::Vector2i) {
	}
}