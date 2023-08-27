#include "CoefficientMovePanelInteraction.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	CoefficientMovePanelInteraction::Make::Make(sf::Vector2f coefficient, sf::Vector2f offset, bool atStart) :
		coefficient(coefficient), offset(offset), atStart(atStart) {
	}
	
	CoefficientMovePanelInteraction* CoefficientMovePanelInteraction::Make::make(PanelActionInitInfo initInfo) {
		return new CoefficientMovePanelInteraction{std::move(*this), initInfo};
	}
	
	CoefficientMovePanelInteraction::CoefficientMovePanelInteraction(Make&& make, PanelActionInitInfo initInfo) :
		BasePanelInteraction(initInfo), coefficient(make.coefficient), offset(make.offset), atStart(make.atStart) {
	}
	
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
		return new CoefficientMovePanelInteraction{*this};
	}
	
	bool DecodePointer<CoefficientMovePanelInteraction>::decodePointer(const YAML::Node& node, CoefficientMovePanelInteraction*& coefficientMovePanelInteraction) {
		sf::Vector2f coefficient;
		sf::Vector2f offset;
		bool atStart{false};
		
		node["coefficient"] >> coefficient;
		node["offset"] >> offset;
		if(node["at-start"])
			node["at-start"] >> atStart;
		
		coefficientMovePanelInteraction = new CoefficientMovePanelInteraction{coefficient, offset, atStart};
		return true;
	}
}