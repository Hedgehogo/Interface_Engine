#include "panelInteraction.hpp"
#include "../../../manager/iPanelManager.hpp"

namespace ui {
	PanelInteraction::PanelInteraction() : panel(nullptr), panelManager(nullptr) {
	}
	
	void PanelInteraction::init(PanelInteractionInitInfo panelInteractionInitInfo) {
		this->panel = &panelInteractionInitInfo.panel;
		this->panelManager = &panelInteractionInitInfo.panelManager;
	}
	
	void PanelInteraction::setPanel(Panel& panel) {
		this->panel = &panel;
	}
	
	void PanelInteraction::copy(PanelInteraction* panelInteraction) {
		panelInteraction->panel = this->panel;
		panelInteraction->panelManager = this->panelManager;
	}
}
