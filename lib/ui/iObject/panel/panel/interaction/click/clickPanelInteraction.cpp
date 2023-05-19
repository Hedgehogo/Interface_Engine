#include "clickPanelInteraction.hpp"
#include "../../../manager/iPanelManager.hpp"

namespace ui {
	ClickPanelInteraction::ClickPanelInteraction(PanelEvent* event, Key key) : OneKeyInteraction(event, key), BasePanelInteraction() {
	}
	
	void ClickPanelInteraction::init(PanelInteractionInitInfo panelInteractionInitInfo) {
		dynamic_cast<PanelEvent*>(event)->init(panelInteractionInitInfo.panel, panelInteractionInitInfo.panelManager);
	}
	
	void ClickPanelInteraction::setPanel(Panel& panel) {
		dynamic_cast<PanelEvent*>(event)->setPanel(panel);
	}
}