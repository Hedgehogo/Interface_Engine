#include "PanelEvent.hpp"
#include "../../../IPanelManager/IPanelManager.hpp"

namespace ie {
	PanelEvent::PanelEvent() : panel(nullptr), panelManager(nullptr) {
	}
	
	void PanelEvent::init(PanelInteractionInitInfo initInfo) {
		this->panel = &initInfo.additional;
		this->panelManager = &initInfo.panelManager;
	}
	
	void PanelEvent::setPanel(Panel& panel) {
		this->panel = &panel;
	}
	
	Panel* PanelEvent::getPanel() {
		return panel;
	}
}
