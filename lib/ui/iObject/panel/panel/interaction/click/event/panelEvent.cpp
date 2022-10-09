#include "panelEvent.hpp"
#include "../../../../manager/iPanelManager.hpp"

namespace ui {
	PanelEvent::PanelEvent() : panel(nullptr), panelManager(nullptr) {
	}
	
	void PanelEvent::init(Panel &panel, IPanelManager &panelManager) {
		this->panel = &panel;
		this->panelManager = &panelManager;
	}
	
	void PanelEvent::setPanel(Panel &panel) {
		this->panel = &panel;
	}
	
	void PanelEvent::copy(PanelEvent *panelEvent) {
		panelEvent->panel = this->panel;
		panelEvent->panelManager = this->panelManager;
	}
	
	Panel *PanelEvent::getPanel() {
		return panel;
	}
}
