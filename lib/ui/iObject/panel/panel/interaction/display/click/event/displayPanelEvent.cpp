#include "displayPanelEvent.h"
#include "../../../../general/panel.hpp"

namespace ui {
	void DisplayPanelEvent::startPressed() {}
	
	void DisplayPanelEvent::whilePressed() {}
	
	void DisplayPanelEvent::stopPressed() {
		panelManager->displayPanel(panel);
	}
	
	void DisplayPanelEvent::whileNotPressed() {}
	
	DisplayPanelEvent *DisplayPanelEvent::copy() {
		DisplayPanelEvent* displayPanelEvent{new DisplayPanelEvent{}};
		displayPanelEvent->init(*panel, *panelManager);
		return displayPanelEvent;
	}

    bool convertPointer(const YAML::Node &node, DisplayPanelEvent *&displayPanelEvent) {
        { displayPanelEvent = new DisplayPanelEvent{}; return true; }
    }
}