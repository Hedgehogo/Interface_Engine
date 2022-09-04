#pragma once
#include "event/panelEvent.hpp"
#include "../hide/hidePanelInteraction.hpp"
#include "../display/displayPanelInteraction.hpp"
#include "../../../../../interaction/iInteraction/oneButton/oneButtonInteraction.hpp"

namespace ui {
	class ClickPanelInteraction : public virtual BasePanelInteraction, public OneButtonInteraction {
	public:
		ClickPanelInteraction(PanelEvent *event, sf::Mouse::Button button);
		
		void init(Panel& panel, PanelManager& panelManager) override;
		
		void setPanel(Panel& panel) override;
		
		ClickPanelInteraction* copy() override = 0;
	};
}
