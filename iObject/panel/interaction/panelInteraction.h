#pragma once
#include "../panel.h"
#include "../../../interaction/iInteraction/iInteraction.h"

namespace ui {
	class PanelInteraction : public IInteraction {
	protected:
		Panel* panel;
		PanelStack* panelStack;
	
	public:
		PanelInteraction() = default;
		
		void init(Panel& panel, PanelStack& panelStack);
		
		void start(sf::Vector2i mousePosition) override = 0;
		
		bool update(sf::Vector2i mousePosition) override = 0;
		
		void finish(sf::Vector2i mousePosition) override = 0;
	};
}
