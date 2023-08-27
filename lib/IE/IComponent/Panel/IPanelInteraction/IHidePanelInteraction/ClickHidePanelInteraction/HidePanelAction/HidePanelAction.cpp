#include "HidePanelAction.hpp"
#include "../../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	HidePanelAction::HidePanelAction(bool onlyOnParent) : onlyOnParent(onlyOnParent) {
	}
	
	void HidePanelAction::startPressed() {
	}
	
	void HidePanelAction::whilePressed() {
	}
	
	void HidePanelAction::stopPressed() {
		sf::Vector2f pointPosition{static_cast<sf::Vector2f>(mousePosition)};
		if(onlyOnParent ? panel->getParentProcessed() : !panel->inPanel(pointPosition) && !panel->inConstPanels(pointPosition) && panel->isFree()) {
			panelManager->hidePanel(panel);
		}
	}
	
	void HidePanelAction::whileNotPressed() {
	}
	
	HidePanelAction* HidePanelAction::copy() {
		return new HidePanelAction{*this};
	}
	
	bool DecodePointer<HidePanelAction>::decodePointer(const YAML::Node& node, HidePanelAction*& hidePanelAction) {
		hidePanelAction = new HidePanelAction{convDef(node["only-on-parent"], false)};
		return true;
	}
}
