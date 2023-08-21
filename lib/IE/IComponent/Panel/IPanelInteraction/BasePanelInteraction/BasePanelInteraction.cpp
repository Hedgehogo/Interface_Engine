#include "BasePanelInteraction.hpp"
#include "../../IPanelManager/IPanelManager.hpp"

namespace ui {
	BasePanelInteraction::BasePanelInteraction() : panel(nullptr), panelManager(nullptr) {
	}
	
	void BasePanelInteraction::init(PanelInteractionInitInfo panelInteractionInitInfo) {
		this->panel = &panelInteractionInitInfo.panel;
		this->panelManager = &panelInteractionInitInfo.panelManager;
	}
	
	void BasePanelInteraction::setPanel(Panel& panel) {
		this->panel = &panel;
	}
	
	void BasePanelInteraction::copy(BasePanelInteraction* panelInteraction) {
		panelInteraction->panel = this->panel;
		panelInteraction->panelManager = this->panelManager;
	}
}
