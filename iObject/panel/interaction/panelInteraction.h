#pragma once
#include "../../../interaction/iInteraction/iInteraction.h"

namespace ui {
	class Panel;
	class PanelManager;
	class PanelInteraction : public IInteraction {
	protected:
		Panel* panel;
		PanelManager* panelStack;
		
		void copy(PanelInteraction* panelInteraction);
	
	public:
		PanelInteraction();
		
		void init(Panel& panel, PanelManager& panelStack);
		
		void setPanel(Panel& panel);
		
		void start(sf::Vector2i mousePosition) override = 0;
		
		bool update(sf::Vector2i mousePosition) override = 0;
		
		void finish(sf::Vector2i mousePosition) override = 0;
		
		PanelInteraction* copy() override = 0;
	};
}
