#include "clickDisplayPanelInteraction.h"
#include "../../../general/panel.h"

namespace ui {
	ClickDisplayPanelInteraction::ClickDisplayPanelInteraction(sf::Mouse::Button button) :
		ClickPanelInteraction(new DisplayPanelEvent{}, button), DisplayPanelInteraction() {}
	
	ClickDisplayPanelInteraction::ClickDisplayPanelInteraction(DisplayPanelEvent *displayPanelEvent, sf::Mouse::Button button) :
		ClickPanelInteraction(displayPanelEvent, button), DisplayPanelInteraction() {}
	
	void ClickDisplayPanelInteraction::start(sf::Vector2i mousePosition) {
		dynamic_cast<PanelEvent*>(event)->getPanel()->setParentProcessed(true);
	}
	
	void ClickDisplayPanelInteraction::finish(sf::Vector2i mousePosition) {
		OneButtonInteraction::finish(mousePosition);
		dynamic_cast<PanelEvent*>(event)->getPanel()->setParentProcessed(false);
	}
	
	ClickDisplayPanelInteraction *ClickDisplayPanelInteraction::copy() {
		ClickDisplayPanelInteraction* clickDisplayPanelInteraction{new ClickDisplayPanelInteraction(dynamic_cast<DisplayPanelEvent*>(event->copy()), button)};
		return clickDisplayPanelInteraction;
	}

    ClickDisplayPanelInteraction *ClickDisplayPanelInteraction::createFromYaml(const YAML::Node &node) {
        sf::Mouse::Button button;
        node["button"] >> button;
        return new ClickDisplayPanelInteraction{button};
    }
}