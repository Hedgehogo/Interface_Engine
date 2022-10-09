#include "dontHidePanelInteraction.hpp"
#include "../../../../manager/iPanelManager.hpp"

namespace ui {
	void DontHidePanelInteraction::init(Panel &panel, IPanelManager &panelManager) {}
	
	void DontHidePanelInteraction::setPanel(Panel &panel) {}
	
	DontHidePanelInteraction *DontHidePanelInteraction::copy() {
		return new DontHidePanelInteraction{};
	}
	
	DontHidePanelInteraction *DontHidePanelInteraction::createFromYaml(const YAML::Node &node) {
		return new DontHidePanelInteraction{};
	}
}