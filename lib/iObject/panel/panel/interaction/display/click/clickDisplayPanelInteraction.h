#pragma once
#include "event/displayPanelEvent.h"
#include "../../click/clickPanelInteraction.h"

namespace ui {
	class ClickDisplayPanelInteraction : public ClickPanelInteraction, public DisplayPanelInteraction {
	public:
		explicit ClickDisplayPanelInteraction(sf::Mouse::Button button);
	
	protected:
		ClickDisplayPanelInteraction(DisplayPanelEvent* displayPanelEvent, sf::Mouse::Button button);
		
		void start(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
	
	public:
		ClickDisplayPanelInteraction* copy() override;
	};
}
