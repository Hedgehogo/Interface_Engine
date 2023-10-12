#pragma once

#include "../WheelAction.hpp"

namespace ie {
	class BaseWheelAction : public WheelAction {
	public:
		explicit BaseWheelAction();
		
		virtual void startPressed(sf::Vector2i mousePosition, int value) = 0;
		
		virtual void stopPressed(sf::Vector2i mousePosition, int value) = 0;
		
		virtual void whilePressed(sf::Vector2i mousePosition, int value) = 0;
		
		virtual void whileNotPressed(sf::Vector2i mousePosition, int value) = 0;
		
		void update(sf::Vector2i mousePosition, int value) override;
	};
}
