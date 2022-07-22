#pragma once
#include "../hidePanelInteraction.h"
#include "../../general/panelInteraction.h"

namespace ui {
	class PointingHidePanelInteraction : public HidePanelInteraction, public PanelInteraction {
	public:
		void start(sf::Vector2i mousePosition) override;
		
		bool update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		PointingHidePanelInteraction* copy() override;
	};
}
