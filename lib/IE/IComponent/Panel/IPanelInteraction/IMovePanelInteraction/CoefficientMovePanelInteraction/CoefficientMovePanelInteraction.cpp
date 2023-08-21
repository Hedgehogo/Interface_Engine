#include "CoefficientMovePanelInteraction.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ui {
	CoefficientMovePanelInteraction::CoefficientMovePanelInteraction(sf::Vector2f coefficient, sf::Vector2f offset, bool atStart) :
		coefficient(coefficient), offset(offset), atStart(atStart) {
	}
	
	bool CoefficientMovePanelInteraction::getAtStart() {
		return atStart;
	}
	
	void CoefficientMovePanelInteraction::move(sf::Vector2i mousePosition) {
		sf::Vector2f panelSize{panel->getSize()};
		sf::Vector2f pointPosition{static_cast<sf::Vector2f>(mousePosition)};
		panel->setPosition({pointPosition.x - panelSize.x * coefficient.x + offset.x, pointPosition.y - panelSize.y * coefficient.y + offset.y});
	}
	
	CoefficientMovePanelInteraction* CoefficientMovePanelInteraction::copy() {
		CoefficientMovePanelInteraction* positioningMovePanelInteraction{new CoefficientMovePanelInteraction{coefficient, offset, false}};
		BasePanelInteraction::copy(positioningMovePanelInteraction);
		return positioningMovePanelInteraction;
	}
	
	bool DecodePointer<CoefficientMovePanelInteraction>::decodePointer(const YAML::Node& node, CoefficientMovePanelInteraction*& coefficientMovePanelInteraction) {
		sf::Vector2f coefficient;
		sf::Vector2f offset;
		bool atStart{false};
		
		node["coefficient"] >> coefficient;
		node["offset"] >> offset;
		if(node["at-start"])
			node["at-start"] >> atStart;
		
		{
			coefficientMovePanelInteraction = new CoefficientMovePanelInteraction{coefficient, offset, atStart};
			return true;
		}
	}
}