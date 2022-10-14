#include "clickHidePanelInteraction.hpp"

namespace ui {
	ClickHidePanelInteraction::ClickHidePanelInteraction(KeyHandler::Key button, bool onlyOnParent) :
		ClickPanelInteraction(new HidePanelEvent{onlyOnParent}, button), HidePanelInteraction() {
	}
	
	ClickHidePanelInteraction::ClickHidePanelInteraction(HidePanelEvent *hidePanelEvent, KeyHandler::Key button) :
		ClickPanelInteraction(hidePanelEvent, button), HidePanelInteraction() {
	}
	
	ClickHidePanelInteraction *ClickHidePanelInteraction::copy() {
		ClickHidePanelInteraction *clickHidePanelInteraction{new ClickHidePanelInteraction(dynamic_cast<HidePanelEvent *>(event->copy()), button)};
		return clickHidePanelInteraction;
	}
	
	bool convertPointer(const YAML::Node &node, ClickHidePanelInteraction *&clickHidePanelInteraction) {
		KeyHandler::Key button;
		bool onlyOnParent{false};
		
		node["button"] >> button;
		if(node["only-on-parent"])
			node["only-on-parent"] >> onlyOnParent;
		
		{ clickHidePanelInteraction = new ClickHidePanelInteraction{button, onlyOnParent}; return true; }
	}
}
