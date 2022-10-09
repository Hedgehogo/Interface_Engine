#include <iostream>
#include "pointingHidePanelInteraction.hpp"
#include "../../../general/panel.hpp"

namespace ui {
	PointingHidePanelInteraction::PointingHidePanelInteraction(bool onlyOnParent) : onlyOnParent(onlyOnParent) {}
	
	void PointingHidePanelInteraction::start(sf::Vector2i) {}
	
	bool PointingHidePanelInteraction::update(sf::Vector2i mousePosition) {
		sf::Vector2f pointPosition{static_cast<sf::Vector2f>(mousePosition)};
		if(!panel->getParentProcessed() && (onlyOnParent || (!panel->inPanel(pointPosition) && panel->isFree() && !panel->inConstPanels(pointPosition)))) {
			panelManager->hidePanel(panel);
		}
		return false;
	}
	
	void PointingHidePanelInteraction::finish(sf::Vector2i) {}
	
	PointingHidePanelInteraction *PointingHidePanelInteraction::copy() {
		PointingHidePanelInteraction *pointingHidePanelInteraction{new PointingHidePanelInteraction{}};
		PanelInteraction::copy(pointingHidePanelInteraction);
		return pointingHidePanelInteraction;
	}
	
	PointingHidePanelInteraction *PointingHidePanelInteraction::createFromYaml(const YAML::Node &node) {
		bool onlyOnParent{false};
		
		if(node["only-on-parent"])
			node["only-on-parent"] >> onlyOnParent;
		
		return new PointingHidePanelInteraction{onlyOnParent};
	}
}
