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

    DisplayPanelEvent *DisplayPanelEvent::createFromYaml(const YAML::Node &node) {
        return new DisplayPanelEvent{};
    }
}