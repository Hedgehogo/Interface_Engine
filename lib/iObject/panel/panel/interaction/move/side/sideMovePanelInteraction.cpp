#include "sideMovePanelInteraction.h"
#include "../../../general/panel.h"

namespace ui {
	SideMovePanelInteraction::SideMovePanelInteraction(float coefficient, float offset, bool horizontal, bool atStart) :
		MovePanelInteraction(atStart), coefficient(coefficient), offset(offset), horizontal(horizontal) {}
	
	void SideMovePanelInteraction::move(sf::Vector2i mousePosition) {
		sf::Vector2f panelSize{panel->getSize()};
		sf::Vector2f panelPosition{panel->getAreaPosition()};
		sf::Vector2f pointPosition{static_cast<sf::Vector2f>(mousePosition)};
		float position = (horizontal ? (pointPosition.x - panelSize.x * coefficient + offset) : (pointPosition.y - panelSize.y * coefficient + offset));
		panel->setPosition((horizontal ? sf::Vector2f{position, panelPosition.y} : sf::Vector2f{panelPosition.x, position}));
	}
	
	SideMovePanelInteraction *SideMovePanelInteraction::copy() {
		SideMovePanelInteraction* sideMovePanelInteraction{new SideMovePanelInteraction{coefficient, offset, horizontal, false}};
		PanelInteraction::copy(sideMovePanelInteraction);
		return sideMovePanelInteraction;
	}
}