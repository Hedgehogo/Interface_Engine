#pragma once
#include "../displayPanelInteraction.h"
#include "../../general/panelInteraction.h"

namespace ui {
	class PointingDisplayPanelInteraction : public DisplayPanelInteraction, public PanelInteraction {
	public:
		PointingDisplayPanelInteraction();
		
		void start(sf::Vector2i mousePosition) override;
		
		bool update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		PointingDisplayPanelInteraction* copy() override;
	};
}
