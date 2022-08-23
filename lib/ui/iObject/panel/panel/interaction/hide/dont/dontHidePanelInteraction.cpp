#include "dontHidePanelInteraction.hpp"

namespace ui {
	void DontHidePanelInteraction::init(Panel &panel, PanelManager &panelManager) {}
	
	void DontHidePanelInteraction::setPanel(Panel &panel) {}
	
	DontHidePanelInteraction *DontHidePanelInteraction::copy() {
		return new DontHidePanelInteraction{};
	}
	
	DontHidePanelInteraction *DontHidePanelInteraction::createFromYaml(const YAML::Node &node) {
		return new DontHidePanelInteraction{};
	}
}