#include "clickHidePanelInteraction.hpp"

namespace ui {
	ClickHidePanelInteraction::ClickHidePanelInteraction(Key button, bool onlyOnParent) :
		ClickPanelInteraction(new HidePanelEvent{onlyOnParent}, button), HidePanelInteraction() {
	}
	
	ClickHidePanelInteraction::ClickHidePanelInteraction(HidePanelEvent *hidePanelEvent, Key button) :
		ClickPanelInteraction(hidePanelEvent, button), HidePanelInteraction() {
	}
	
	ClickHidePanelInteraction *ClickHidePanelInteraction::copy() {
		ClickHidePanelInteraction *clickHidePanelInteraction{new ClickHidePanelInteraction(dynamic_cast<HidePanelEvent *>(event->copy()), button)};
		return clickHidePanelInteraction;
	}
	
	ClickHidePanelInteraction *ClickHidePanelInteraction::createFromYaml(const YAML::Node &node) {
		Key button;
		bool onlyOnParent{false};
		
		node["button"] >> button;
		if(node["only-on-parent"])
			node["only-on-parent"] >> onlyOnParent;
		
		return new ClickHidePanelInteraction{button, onlyOnParent};
	}
}
