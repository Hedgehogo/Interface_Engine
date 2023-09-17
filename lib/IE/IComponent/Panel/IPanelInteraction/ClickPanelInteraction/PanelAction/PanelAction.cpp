#include "PanelAction.hpp"
#include "../../../IPanelManager/IPanelManager.hpp"

namespace ie {
	PanelAction::PanelAction(PanelActionInitInfo initInfo) :
		panel(&initInfo.additional), panelManager(&initInfo.panelManager) {
	}
	
	PanelAction::PanelAction() : panel(nullptr), panelManager(nullptr) {
	}
	
	void PanelAction::init(PanelActionInitInfo initInfo) {
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
