#include <iostream>
#include "pointingHidePanelInteraction.h"
#include "../../../general/panel.h"

void ui::PointingHidePanelInteraction::start(sf::Vector2i) {
	//std::cout << "start hide: " << panel << "\n";
}

bool ui::PointingHidePanelInteraction::update(sf::Vector2i mousePosition) {
	/*if(panel->isFree()) {
		std::cout << "active";
		if(!panel->getParentProcessed()) {
			std::cout << ", !parent";
			if(!panel->inPanel(static_cast<sf::Vector2f>(mousePosition))) {
				panelManager->hidePanel(panel);
				std::cout << ", !in panel";
			}
		}
		std::cout << ": " << panel << "\n";
	}*/
	//std::cout << (panel->isFree() ? "active: " : "not active: ") << panel << std::endl;
	if(panel->isFree() && !panel->getParentProcessed() && !panel->inPanel(static_cast<sf::Vector2f>(mousePosition))) {
		panelManager->hidePanel(panel);
		//std::cout << "hide: " << panel << "\n";
	}
	return false;
}

void ui::PointingHidePanelInteraction::finish(sf::Vector2i) {
	//std::cout << "true hide: " << panel << "\n";
}

ui::PointingHidePanelInteraction *ui::PointingHidePanelInteraction::copy() {
	PointingHidePanelInteraction* pointingHidePanelInteraction {new PointingHidePanelInteraction{}};
	pointingHidePanelInteraction->panel = this->panel;
	pointingHidePanelInteraction->panelManager = this->panelManager;
	return pointingHidePanelInteraction;
}
