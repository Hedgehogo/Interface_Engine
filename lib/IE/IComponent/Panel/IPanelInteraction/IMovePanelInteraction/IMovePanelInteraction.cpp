#include "IMovePanelInteraction.hpp"

namespace ui {
	void IMovePanelInteraction::start(sf::Vector2i mousePosition) {
		if(getAtStart())
			move(mousePosition);
	}
	
	void IMovePanelInteraction::update(sf::Vector2i mousePosition) {
		if(!getAtStart())
			move(mousePosition);
	}
	
	void IMovePanelInteraction::finish(sf::Vector2i) {
	}
}