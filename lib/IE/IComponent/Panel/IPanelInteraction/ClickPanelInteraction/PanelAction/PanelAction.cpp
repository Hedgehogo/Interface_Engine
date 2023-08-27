#include "PanelAction.hpp"
#include "../../../IPanelManager/IPanelManager.hpp"

namespace ie {
	PanelAction::PanelAction() : panel(nullptr), panelManager(nullptr) {
	}
	
	void PanelAction::init(PanelInteractionInitInfo initInfo) {
		this->panel = &initInfo.additional;
		this->panelManager = &initInfo.panelManager;
	}
	
	void PanelAction::setPanel(Panel& panel) {
		this->panel = &panel;
	}
	
	Panel* PanelAction::getPanel() {
		return panel;
	}
}
