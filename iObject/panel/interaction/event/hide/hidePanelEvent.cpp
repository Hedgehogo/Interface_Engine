#include <iostream>
#include "hidePanelEvent.h"
#include "../../../panelManager/panelManager.h"

void ui::HidePanelEvent::startPressed(sf::Vector2i windowPosition) {}

void ui::HidePanelEvent::whilePressed(sf::Vector2i windowPosition) {}

void ui::HidePanelEvent::stopPressed(sf::Vector2i windowPosition) {
	//std::cout << "click" << std::endl;
	if(!panel->inPanel(static_cast<sf::Vector2f>(windowPosition)))
		panelManager->hidePanel(panel);
}

void ui::HidePanelEvent::whileNotPressed(sf::Vector2i windowPosition) {}

ui::HidePanelEvent *ui::HidePanelEvent::copy() {
	HidePanelEvent* hidePanelEvent{new HidePanelEvent()};
	hidePanelEvent->init(*panel, *panelManager);
	return hidePanelEvent;
}
