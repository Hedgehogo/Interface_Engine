#pragma once
#include "../event/panelEvent.h"
#include "../hide/hidePanelInteraction.h"
#include "../../../../interaction/iInteraction/oneButton/oneButtonInteraction.h"

namespace ui {
	class ClickPanelInteraction : public virtual BasePanelInteraction, public OneButtonInteraction {
	public:
		ClickPanelInteraction(PanelEvent *event, sf::Mouse::Button button);
		
		void init(Panel& panel, PanelManager& panelStack) override;
		
		void setPanel(Panel& panel) override;
		
		ClickPanelInteraction* copy() override;
	};
}
