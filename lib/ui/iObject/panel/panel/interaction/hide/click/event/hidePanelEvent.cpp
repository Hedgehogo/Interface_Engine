#include "hidePanelEvent.hpp"
#include "../../../../general/panel.hpp"

namespace ui {
	HidePanelEvent::HidePanelEvent(bool onlyOnParent) : onlyOnParent(onlyOnParent) {
	}
	
	void HidePanelEvent::startPressed() {
	}
	
	void HidePanelEvent::whilePressed() {
	}
	
	void HidePanelEvent::stopPressed() {
		sf::Vector2f pointPosition{static_cast<sf::Vector2f>(mousePosition)};
		if(onlyOnParent ? panel->getParentProcessed() : !panel->inPanel(pointPosition) && !panel->inConstPanels(pointPosition) && panel->isFree())
			panelManager->hidePanel(panel);
	}
	
	void HidePanelEvent::whileNotPressed() {
	}
	
	HidePanelEvent* HidePanelEvent::copy() {
		HidePanelEvent* hidePanelEvent{new HidePanelEvent()};
		PanelEvent::copy(hidePanelEvent);
		return hidePanelEvent;
	}
	
	
	bool DecodePointer<HidePanelEvent>::decodePointer(const YAML::Node& node, HidePanelEvent*& hidePanelEvent) {
		bool onlyOnParent{false};
		
		if(node["only-on-parent"])
			node["only-on-parent"] >> onlyOnParent;
		
		{
			hidePanelEvent = new HidePanelEvent{onlyOnParent};
			return true;
		}
	}
}
