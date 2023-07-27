#include "displayPanelEvent.hpp"
#include "../../../../general/panel.hpp"

namespace ui {
	void DisplayPanelEvent::startPressed() {
	}
	
	void DisplayPanelEvent::whilePressed() {
	}
	
	void DisplayPanelEvent::stopPressed() {
		panelManager->displayPanel(panel);
	}
	
	void DisplayPanelEvent::whileNotPressed() {
	}
	
	DisplayPanelEvent* DisplayPanelEvent::copy() {
		DisplayPanelEvent* displayPanelEvent{new DisplayPanelEvent{}};
		PanelEvent::copy(displayPanelEvent);
		return displayPanelEvent;
	}
}