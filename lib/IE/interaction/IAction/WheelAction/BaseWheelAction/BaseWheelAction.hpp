#pragma once

#include "../WheelAction.hpp"

namespace ie {
	class BaseWheelAction : public WheelAction {
	public:
		explicit BaseWheelAction();
		
		virtual void start_pressed(sf::Vector2i mouse_position, int value) = 0;
		
		virtual void stop_pressed(sf::Vector2i mouse_position, int value) = 0;
		
		virtual void while_pressed(sf::Vector2i mouse_position, int value) = 0;
		
		virtual void while_not_pressed(sf::Vector2i mouse_position, int value) = 0;
		
		void update(sf::Vector2i mouse_position, int value) override;
	};
}
