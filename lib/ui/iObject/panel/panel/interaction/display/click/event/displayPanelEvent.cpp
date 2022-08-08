#include "displayPanelEvent.h"
#include "../../../../general/panel.h"

namespace ui {
	void DisplayPanelEvent::startPressed(sf::Vector2i) {}
	
	void DisplayPanelEvent::whilePressed(sf::Vector2i) {}
	
	void DisplayPanelEvent::stopPressed(sf::Vector2i) {
		panelManager->displayPanel(panel);
	}
	
	void DisplayPanelEvent::whileNotPressed(sf::Vector2i) {}
	
	DisplayPanelEvent *DisplayPanelEvent::copy() {
		DisplayPanelEvent* displayPanelEvent{new DisplayPanelEvent{}};
		displayPanelEvent->init(*panel, *panelManager);
		return displayPanelEvent;
	}
}