#include <iostream>
#include "pointingHidePanelInteraction.h"
#include "../../panelManager/panelManager.h"

void ui::PointingHidePanelInteraction::start(sf::Vector2i) {
	std::cout << "start hide: " << panel << "\n";
}

bool ui::PointingHidePanelInteraction::update(sf::Vector2i mousePosition) {
	/*if(panel->isActive()) {
		std::cout << "active";
		if(!panel->getParentProcessed()) {
			std::cout << ", !parent";
			if(!panel->inPanel(static_cast<sf::Vector2f>(mousePosition))) {
				panelStack->hidePanel(panel);
				std::cout << ", !in panel";
			}
		}
		std::cout << ": " << panel << "\n";
	}*/
	if(panel->isActive() && !panel->getParentProcessed() && !panel->inPanel(static_cast<sf::Vector2f>(mousePosition))) {
		panelStack->hidePanel(panel);
		std::cout << "hide: " << panel << "\n";
	}
	return false;
}

void ui::PointingHidePanelInteraction::finish(sf::Vector2i) {
	std::cout << "true hide: " << panel << "\n";
}

ui::PointingHidePanelInteraction *ui::PointingHidePanelInteraction::copy() {
	PointingHidePanelInteraction* pointingHidePanelInteraction {new PointingHidePanelInteraction{}};
	pointingHidePanelInteraction->panel = this->panel;
	pointingHidePanelInteraction->panelStack = this->panelStack;
	return pointingHidePanelInteraction;
}
