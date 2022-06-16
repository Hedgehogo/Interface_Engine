#pragma once
#include "../buttonEvent.h"

namespace ui {
	class ButtonEvent_Simple : public ButtonEvent {
	protected:
		virtual void startPressed(sf::Vector2i windowPosition) = 0;
		
		virtual void stopPressed (sf::Vector2i windowPosition) = 0;
		
		virtual void whilePressed(sf::Vector2i windowPosition) = 0;
		
		virtual void whileNotPressed  (sf::Vector2i windowPosition) = 0;
	public:
		ButtonEvent_Simple();
		void update(sf::Vector2i mousePosition, bool press) override;
	};
}
