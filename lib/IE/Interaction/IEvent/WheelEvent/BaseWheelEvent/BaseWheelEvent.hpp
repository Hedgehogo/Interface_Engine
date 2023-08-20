#pragma once

#include "../WheelEvent.hpp"

namespace ui {
	class WheelEvent_Simple : public WheelEvent {
	public:
		explicit WheelEvent_Simple();
		
		virtual void startPressed(sf::Vector2i mousePosition, int value) = 0;
		
		virtual void stopPressed(sf::Vector2i mousePosition, int value) = 0;
		
		virtual void whilePressed(sf::Vector2i mousePosition, int value) = 0;
		
		virtual void whileNotPressed(sf::Vector2i mousePosition, int value) = 0;
		
		void update(sf::Vector2i mousePosition, int value) override;
	};
}
