#include "movePanelInteraction.h"

namespace ui {
	ui::MovePanelInteraction::MovePanelInteraction(bool atStart) : atStart(atStart) {}
	
	void MovePanelInteraction::start(sf::Vector2i mousePosition) {
		if(atStart)
			move(mousePosition);
	}
	
	bool MovePanelInteraction::update(sf::Vector2i mousePosition) {
		if(!atStart)
			move(mousePosition);
		return false;
	}
	
	void MovePanelInteraction::finish(sf::Vector2i mousePosition) {}
}