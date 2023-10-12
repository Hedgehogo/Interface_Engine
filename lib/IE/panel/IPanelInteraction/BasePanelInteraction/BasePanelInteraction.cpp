#include "BasePanelInteraction.hpp"
#include "../../IPanelManager/IPanelManager.hpp"

namespace ie {
	BasePanelInteraction::BasePanelInteraction(PanelActionInitInfo initInfo) :
		panel(&initInfo.additional), panelManager(&initInfo.panelManager) {
	}
	
	BasePanelInteraction::BasePanelInteraction() : panel(nullptr), panelManager(nullptr) {
	}
	
	void BasePanelInteraction::init(PanelActionInitInfo initInfo) {
		this->panel = &initInfo.additional;
		this->panelManager = &initInfo.panelManager;
	}
	
	void BasePanelInteraction::setPanel(Panel& panel) {
		this->panel = &panel;
	}
}
