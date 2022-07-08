#pragma once
#include "../panelEvent.h"

namespace ui {
	class HidePanelEvent : public PanelEvent {
	protected:
		void startPressed   (sf::Vector2i mousePosition) override;
		
		void whilePressed   (sf::Vector2i mousePosition) override;
		
		void stopPressed    (sf::Vector2i mousePosition) override;
		
		void whileNotPressed(sf::Vector2i mousePosition) override;
		
	public:
		HidePanelEvent* copy() override;
	};
}
