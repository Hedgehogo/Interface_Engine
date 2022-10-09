#include "clickPanelInteraction.hpp"
#include "../../../manager/iPanelManager.hpp"

namespace ui {
	ClickPanelInteraction::ClickPanelInteraction(PanelEvent *event, Key button) : OneButtonInteraction(event, button), BasePanelInteraction() {}
	
	void ClickPanelInteraction::init(Panel &panel, IPanelManager &panelManager) {
		dynamic_cast<PanelEvent *>(event)->init(panel, panelManager);
	}
	
	void ClickPanelInteraction::setPanel(Panel &panel) {
		dynamic_cast<PanelEvent *>(event)->setPanel(panel);
	}
}