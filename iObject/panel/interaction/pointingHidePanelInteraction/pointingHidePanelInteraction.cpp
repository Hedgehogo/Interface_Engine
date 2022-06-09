#include <iostream>
#include "pointingHidePanelInteraction.h"
#include "../../panelStack/panelStack.h"

void ui::PointingHidePanelInteraction::start(sf::Vector2i) {}

bool ui::PointingHidePanelInteraction::update(sf::Vector2i mousePosition) {
	if(panel->isActive() && !panel->getParentProcessed() && !panel->inPanel(static_cast<sf::Vector2f>(mousePosition))) {
		panelStack->hidePanel(panel);
		panel->hide();
	}
	return false;
}

void ui::PointingHidePanelInteraction::finish(sf::Vector2i) {}
