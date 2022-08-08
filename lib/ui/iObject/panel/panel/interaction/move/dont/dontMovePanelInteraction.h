#pragma once
#include "../movePanelInteraction.h"
#include "../../../../../../interaction/iInteraction/empty/emptyInteraction.h"

namespace ui {
	class DontMovePanelInteraction : public MovePanelInteraction {
	public:
		DontMovePanelInteraction();
		
		void move(sf::Vector2i mousePosition) override;
		
		void start(sf::Vector2i mousePosition) override;
		
		bool update(sf::Vector2i mousePosition) override;
		
		void init(Panel& panel, PanelManager& panelManager) override;
		
		void setPanel(Panel& panel) override;
		
		DontMovePanelInteraction* copy() override;
	};
}
