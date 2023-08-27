#include "SideMovePanelInteraction.hpp"
#include "../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	SideMovePanelInteraction::Make::Make(float coefficient, float offset, bool horizontal, bool atStart) :
		coefficient(coefficient), offset(offset), horizontal(horizontal), atStart(atStart) {
	}
	
	SideMovePanelInteraction* SideMovePanelInteraction::Make::make(PanelActionInitInfo initInfo) {
		return new SideMovePanelInteraction{std::move(*this), initInfo};
	}
	
	SideMovePanelInteraction::SideMovePanelInteraction(Make&& make, PanelActionInitInfo initInfo) :
		BasePanelInteraction(initInfo), coefficient(make.coefficient), offset(make.offset), horizontal(make.horizontal), atStart(make.atStart) {
	}
	
	SideMovePanelInteraction::SideMovePanelInteraction(float coefficient, float offset, bool horizontal, bool atStart) :
		coefficient(coefficient), offset(offset), horizontal(horizontal), atStart(atStart) {
	}
	
	bool SideMovePanelInteraction::getAtStart() {
		return atStart;
	}
	
	void SideMovePanelInteraction::move(sf::Vector2i mousePosition) {
		sf::Vector2f panelSize{panel->getSize()};
		sf::Vector2f panelPosition{panel->getAreaPosition()};
		sf::Vector2f pointPosition{static_cast<sf::Vector2f>(mousePosition)};
		float position = (horizontal ? (pointPosition.x - panelSize.x * coefficient + offset) : (pointPosition.y - panelSize.y * coefficient + offset));
		panel->setPosition((horizontal ? sf::Vector2f{position, panelPosition.y} : sf::Vector2f{panelPosition.x, position}));
	}
	
	SideMovePanelInteraction* SideMovePanelInteraction::copy() {
		return new SideMovePanelInteraction{*this};
	}
	
	bool DecodePointer<SideMovePanelInteraction>::decodePointer(const YAML::Node& node, SideMovePanelInteraction*& sideMovePanelInteraction) {
		float coefficient;
		float offset;
		bool horizontal;
		bool atStart = false;
		
		node["coefficient"] >> coefficient;
		node["offset"] >> offset;
		node["horizontal"] >> horizontal;
		if(node["at-start"])
			node["at-start"] >> atStart;
		
		sideMovePanelInteraction = new SideMovePanelInteraction{coefficient, offset, horizontal, atStart};
		return true;
	}
}