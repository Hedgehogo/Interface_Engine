#include "clickDisplayPanelInteraction.hpp"
#include "../../../general/panel.hpp"

namespace ui {
	ClickDisplayPanelInteraction::ClickDisplayPanelInteraction(Key key) :
		ClickPanelInteraction(new DisplayPanelEvent{}, key), DisplayPanelInteraction() {}
	
	ClickDisplayPanelInteraction::ClickDisplayPanelInteraction(DisplayPanelEvent *displayPanelEvent, Key key) :
		ClickPanelInteraction(displayPanelEvent, key), DisplayPanelInteraction() {}
	
	void ClickDisplayPanelInteraction::start(sf::Vector2i mousePosition) {
		dynamic_cast<PanelEvent*>(event)->getPanel()->setParentProcessed(true);
	}
	
	void ClickDisplayPanelInteraction::finish(sf::Vector2i mousePosition) {
		OneKeyInteraction::finish(mousePosition);
		dynamic_cast<PanelEvent*>(event)->getPanel()->setParentProcessed(false);
	}
	
	ClickDisplayPanelInteraction *ClickDisplayPanelInteraction::copy() {
		ClickDisplayPanelInteraction* clickDisplayPanelInteraction{new ClickDisplayPanelInteraction(dynamic_cast<DisplayPanelEvent*>(event->copy()), key)};
		return clickDisplayPanelInteraction;
	}

    bool convertPointer(const YAML::Node &node, ClickDisplayPanelInteraction *&clickDisplayPanelInteraction) {
        Key key;
        node["key"] >> key;
        { clickDisplayPanelInteraction = new ClickDisplayPanelInteraction{key}; return true; }
    }
}