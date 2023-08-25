#include "ClickPanelInteraction.hpp"
#include "../../IPanelManager/IPanelManager.hpp"

namespace ui {
	ClickPanelInteraction::ClickPanelInteraction(BoxPtr<PanelEvent>&& event, Key key) :
		BasicOneKeyInteraction<Panel&>(dynamicCast<BasicKeyEvent<Panel&> >(std::move(event)), key) {
	}
	
	void ClickPanelInteraction::init(PanelInteractionInitInfo initInfo) {
		dynamic_cast<PanelEvent&>(*event).init(initInfo);
	}
	
	void ClickPanelInteraction::setPanel(Panel& panel) {
		dynamic_cast<PanelEvent&>(*event).setPanel(panel);
	}
}