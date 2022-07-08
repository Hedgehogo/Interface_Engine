#include <iostream>
#include "hidePanelEvent.h"
#include "../../../general/panel.h"

void ui::HidePanelEvent::startPressed(sf::Vector2i) {}

void ui::HidePanelEvent::whilePressed(sf::Vector2i) {}

void ui::HidePanelEvent::stopPressed(sf::Vector2i mousePosition) {
	//std::cout << "click" << std::endl;
	if(!panel->inPanel(static_cast<sf::Vector2f>(mousePosition)))
		panelManager->hidePanel(panel);
}

void ui::HidePanelEvent::whileNotPressed(sf::Vector2i) {}

ui::HidePanelEvent *ui::HidePanelEvent::copy() {
	HidePanelEvent* hidePanelEvent{new HidePanelEvent()};
	hidePanelEvent->init(*panel, *panelManager);
	return hidePanelEvent;
}
