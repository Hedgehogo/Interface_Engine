#include "clickPanelInteraction.hpp"
#include "../../../manager/iPanelManager.hpp"

namespace ui {
	ClickPanelInteraction::ClickPanelInteraction(BoxPtr<PanelEvent>&& event, Key key) :
		OneKeyInteraction(dynamicCast<KeyEvent>(std::move(event)), key) {
	}
	
	void ClickPanelInteraction::init(PanelInteractionInitInfo panelInteractionInitInfo) {
		dynamic_cast<PanelEvent&>(*event).init(panelInteractionInitInfo);
	}
	
	void ClickPanelInteraction::setPanel(Panel& panel) {
		dynamic_cast<PanelEvent&>(*event).setPanel(panel);
	}
}