#pragma once

#include "../BasicTouchAction.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicBaseTouchAction : public virtual BasicTouchAction<T> {
	public:
		BasicBaseTouchAction() = default;
		
		auto set_pressed(bool pressed) -> void override;
		
		auto update(sf::Vector2i point_position, bool press) -> void override;
	
	protected:
		virtual auto start_pressed() -> void = 0;
		
		virtual auto stop_pressed() -> void = 0;
		
		virtual auto while_pressed() -> void = 0;
		
		virtual auto while_not_pressed() -> void = 0;
		
		sf::Vector2i point_position_;
	};
	
	using BaseTouchAction = BasicBaseTouchAction<>;
}

#include "BasicBaseTouchAction.inl"
