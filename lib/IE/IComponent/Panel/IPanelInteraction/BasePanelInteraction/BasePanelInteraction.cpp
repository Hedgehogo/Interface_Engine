#include "BasePanelInteraction.hpp"
#include "../../IPanelManager/IPanelManager.hpp"

namespace ui {
	BasePanelInteraction::BasePanelInteraction() : panel(nullptr), panelManager(nullptr) {
	}
	
	void BasePanelInteraction::init(PanelInteractionInitInfo initInfo) {
		this->panel = &initInfo.additional;
		this->panelManager = &initInfo.panelManager;
	}
	
	void BasePanelInteraction::setPanel(Panel& panel) {
		this->panel = &panel;
	}
}
