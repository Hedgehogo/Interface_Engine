#include "dontHidePanelInteraction.hpp"
#include "../../../../manager/iPanelManager.hpp"

namespace ui {
	void DontHidePanelInteraction::init(Panel &panel, IPanelManager &panelManager) {}
	
	void DontHidePanelInteraction::setPanel(Panel &panel) {}
	
	DontHidePanelInteraction *DontHidePanelInteraction::copy() {
		return new DontHidePanelInteraction{};
	}
	
	bool convertPointer(const YAML::Node &node, DontHidePanelInteraction *&dontHidePanelInteraction) {
		{ dontHidePanelInteraction = new DontHidePanelInteraction{}; return true; }
	}
	
	bool DecodePointer<DontHidePanelInteraction>::decodePointer(const YAML::Node &node, DontHidePanelInteraction *&dontHidePanelInteraction) {
		{ dontHidePanelInteraction = new DontHidePanelInteraction{}; return true; }
	}
}