#include "HidePanelEvent.hpp"
#include "../../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	HidePanelEvent::HidePanelEvent(bool onlyOnParent) : onlyOnParent(onlyOnParent) {
	}
	
	void HidePanelEvent::startPressed() {
	}
	
	void HidePanelEvent::whilePressed() {
	}
	
	void HidePanelEvent::stopPressed() {
		sf::Vector2f pointPosition{static_cast<sf::Vector2f>(mousePosition)};
		if(onlyOnParent ? panel->getParentProcessed() : !panel->inPanel(pointPosition) && !panel->inConstPanels(pointPosition) && panel->isFree()) {
			panelManager->hidePanel(panel);
		}
	}
	
	void HidePanelEvent::whileNotPressed() {
	}
	
	HidePanelEvent* HidePanelEvent::copy() {
		return new HidePanelEvent{*this};
	}
	
	bool DecodePointer<HidePanelEvent>::decodePointer(const YAML::Node& node, HidePanelEvent*& hidePanelEvent) {
		hidePanelEvent = new HidePanelEvent{convDef(node["only-on-parent"], false)};
		return true;
	}
}
