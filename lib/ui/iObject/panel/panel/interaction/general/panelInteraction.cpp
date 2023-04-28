#include "panelInteraction.hpp"
#include "../../../manager/iPanelManager.hpp"

namespace ui {
	PanelInteraction::PanelInteraction() : panel(nullptr), panelManager(nullptr) {
	}
	
	void PanelInteraction::init(Panel& panel, IPanelManager& panelManager) {
		this->panel = &panel;
		this->panelManager = &panelManager;
	}
	
	void PanelInteraction::setPanel(Panel& panel) {
		this->panel = &panel;
	}
	
	void PanelInteraction::copy(PanelInteraction* panelInteraction) {
		panelInteraction->panel = this->panel;
		panelInteraction->panelManager = this->panelManager;
	}
}
