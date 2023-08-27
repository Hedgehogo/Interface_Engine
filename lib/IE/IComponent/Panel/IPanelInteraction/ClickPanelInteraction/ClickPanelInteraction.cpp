#include "ClickPanelInteraction.hpp"
#include "../../IPanelManager/IPanelManager.hpp"

namespace ie {
	ClickPanelInteraction::ClickPanelInteraction(BoxPtr<PanelAction>&& action, Key key, PanelActionInitInfo initInfo) :
		BasicOneKeyInteraction<Panel&>({std::move(action), key}, initInfo) {
	}
	
	ClickPanelInteraction::ClickPanelInteraction(BoxPtr<PanelAction>&& action, Key key) :
		BasicOneKeyInteraction<Panel&>(std::move(action), key) {
	}
	
	void ClickPanelInteraction::init(PanelActionInitInfo initInfo) {
		dynamic_cast<PanelAction&>(*action).init(initInfo);
	}
	
	void ClickPanelInteraction::setPanel(Panel& panel) {
		dynamic_cast<PanelAction&>(*action).setPanel(panel);
	}
}