#pragma once

#include "../WheelEvent.hpp"

namespace ie {
	class BaseWheelEvent : public WheelEvent {
	public:
		explicit BaseWheelEvent();
		
		virtual void startPressed(sf::Vector2i mousePosition, int value) = 0;
		
		virtual void stopPressed(sf::Vector2i mousePosition, int value) = 0;
		
		virtual void whilePressed(sf::Vector2i mousePosition, int value) = 0;
		
		virtual void whileNotPressed(sf::Vector2i mousePosition, int value) = 0;
		
		void update(sf::Vector2i mousePosition, int value) override;
	};
}
