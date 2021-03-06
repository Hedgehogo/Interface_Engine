#include "coefficientMovePanelInteraction.h"
#include "../../../general/panel.h"

namespace ui {
	CoefficientMovePanelInteraction::CoefficientMovePanelInteraction(sf::Vector2f coefficient, sf::Vector2f offset, bool atStart) :
		MovePanelInteraction(atStart), coefficient(coefficient), offset(offset) {}
	
	void CoefficientMovePanelInteraction::move(sf::Vector2i mousePosition) {
		sf::Vector2f panelSize{panel->getSize()};
		sf::Vector2f pointPosition{static_cast<sf::Vector2f>(mousePosition)};
		panel->setPosition({pointPosition.x - panelSize.x * coefficient.x + offset.x, pointPosition.y - panelSize.y * coefficient.y + offset.y});
	}
	
	CoefficientMovePanelInteraction *CoefficientMovePanelInteraction::copy() {
		CoefficientMovePanelInteraction* positioningMovePanelInteraction{new CoefficientMovePanelInteraction{coefficient, offset, false}};
		PanelInteraction::copy(positioningMovePanelInteraction);
		return positioningMovePanelInteraction;
	}
}