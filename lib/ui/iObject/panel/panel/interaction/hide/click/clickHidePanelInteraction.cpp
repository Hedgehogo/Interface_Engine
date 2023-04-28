#include "clickHidePanelInteraction.hpp"

namespace ui {
	ClickHidePanelInteraction::ClickHidePanelInteraction(Key key, bool onlyOnParent) :
		ClickPanelInteraction(new HidePanelEvent{onlyOnParent}, key), HidePanelInteraction() {
	}
	
	ClickHidePanelInteraction::ClickHidePanelInteraction(HidePanelEvent *hidePanelEvent, Key key) :
		ClickPanelInteraction(hidePanelEvent, key), HidePanelInteraction() {
	}
	
	ClickHidePanelInteraction *ClickHidePanelInteraction::copy() {
		ClickHidePanelInteraction *clickHidePanelInteraction{new ClickHidePanelInteraction(dynamic_cast<HidePanelEvent *>(event->copy()), key)};
		return clickHidePanelInteraction;
	}
	
	bool convertPointer(const YAML::Node &node, ClickHidePanelInteraction *&clickHidePanelInteraction) {
		Key key;
		bool onlyOnParent{false};
		
		node["key"] >> key;
		if(node["only-on-parent"])
			node["only-on-parent"] >> onlyOnParent;
		
		{ clickHidePanelInteraction = new ClickHidePanelInteraction{key, onlyOnParent}; return true; }
	}
	
	bool DecodePointer<ClickHidePanelInteraction>::decodePointer(const YAML::Node &node, ClickHidePanelInteraction *&clickHidePanelInteraction) {
		Key key;
		bool onlyOnParent{false};
		
		node["key"] >> key;
		if(node["only-on-parent"])
			node["only-on-parent"] >> onlyOnParent;
		
		{ clickHidePanelInteraction = new ClickHidePanelInteraction{key, onlyOnParent}; return true; }
	}
}
