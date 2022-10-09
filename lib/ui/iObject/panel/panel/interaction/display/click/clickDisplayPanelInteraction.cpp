#include "clickDisplayPanelInteraction.hpp"
#include "../../../general/panel.hpp"

namespace ui {
	ClickDisplayPanelInteraction::ClickDisplayPanelInteraction(Key button) :
		ClickPanelInteraction(new DisplayPanelEvent{}, button), DisplayPanelInteraction() {}
	
	ClickDisplayPanelInteraction::ClickDisplayPanelInteraction(DisplayPanelEvent *displayPanelEvent, Key button) :
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
        Key button;
        node["button"] >> button;
        return new ClickDisplayPanelInteraction{button};
    }
}