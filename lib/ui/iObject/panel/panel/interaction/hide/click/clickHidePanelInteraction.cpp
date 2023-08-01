#include "clickHidePanelInteraction.hpp"

namespace ui {
	ClickHidePanelInteraction::ClickHidePanelInteraction(Key key, bool onlyOnParent) :
		ClickPanelInteraction(new HidePanelEvent{onlyOnParent}, key), IHidePanelInteraction() {
	}
	
	ClickHidePanelInteraction::ClickHidePanelInteraction(HidePanelEvent* hidePanelEvent, Key key) :
		ClickPanelInteraction(hidePanelEvent, key), IHidePanelInteraction() {
	}
	
	ClickHidePanelInteraction* ClickHidePanelInteraction::copy() {
		ClickHidePanelInteraction* clickHidePanelInteraction{new ClickHidePanelInteraction(dynamic_cast<HidePanelEvent*>(event->copy()), key)};
		return clickHidePanelInteraction;
	}
	
	
	bool DecodePointer<ClickHidePanelInteraction>::decodePointer(const YAML::Node& node, ClickHidePanelInteraction*& clickHidePanelInteraction) {
		Key key;
		bool onlyOnParent{false};
		
		node["key"] >> key;
		if(node["only-on-parent"])
			node["only-on-parent"] >> onlyOnParent;
		
		{
			clickHidePanelInteraction = new ClickHidePanelInteraction{key, onlyOnParent};
			return true;
		}
	}
}
