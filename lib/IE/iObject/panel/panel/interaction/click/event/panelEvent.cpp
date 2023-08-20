#include "panelEvent.hpp"
#include "../../../../manager/iPanelManager.hpp"

namespace ui {
	PanelEvent::PanelEvent() : panel(nullptr), panelManager(nullptr) {
	}
	
	void PanelEvent::init(PanelInteractionInitInfo panelInteractionInitInfo) {
		this->panel = &panelInteractionInitInfo.panel;
		this->panelManager = &panelInteractionInitInfo.panelManager;
	}
	
	void PanelEvent::setPanel(Panel& panel) {
		this->panel = &panel;
	}
	
	Panel* PanelEvent::getPanel() {
		return panel;
	}
}
