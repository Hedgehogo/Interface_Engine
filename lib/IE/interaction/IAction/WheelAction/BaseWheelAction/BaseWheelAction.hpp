#pragma once

#include "../WheelAction.hpp"

namespace ie {
	class BaseWheelAction : public WheelAction {
	public:
		explicit BaseWheelAction();
		
		virtual auto start_pressed(sf::Vector2i mouse_position, int value) -> void = 0;
		
		virtual auto stop_pressed(sf::Vector2i mouse_position, int value) -> void = 0;
		
		virtual auto while_pressed(sf::Vector2i mouse_position, int value) -> void = 0;
		
		virtual auto while_not_pressed(sf::Vector2i mouse_position, int value) -> void = 0;
		
		auto update(sf::Vector2i mouse_position, int value) -> void override;
	};
}
