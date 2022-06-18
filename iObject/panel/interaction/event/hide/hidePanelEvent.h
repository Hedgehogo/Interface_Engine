#pragma once
#include "../panelEvent.h"

namespace ui {
	class HidePanelEvent : public PanelEvent {
	protected:
		void startPressed   (sf::Vector2i windowPosition) override;
		
		void whilePressed   (sf::Vector2i windowPosition) override;
		
		void stopPressed    (sf::Vector2i windowPosition) override;
		
		void whileNotPressed(sf::Vector2i windowPosition) override;
		
	public:
		HidePanelEvent* copy() override;
	};
}
