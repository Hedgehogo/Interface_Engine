#pragma once

#include "../BasicKeyAction.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicBaseKeyAction : public virtual BasicKeyAction<T> {
	public:
		BasicBaseKeyAction() = default;
		
		auto set_pressed(bool pressed) -> void override;
		
		auto update(sf::Vector2i mouse_position, bool press) -> void override;
	
	protected:
		virtual auto start_pressed() -> void = 0;
		
		virtual auto stop_pressed() -> void = 0;
		
		virtual auto while_pressed() -> void = 0;
		
		virtual auto while_not_pressed() -> void = 0;
		
		sf::Vector2i mouse_position_;
	};
	
	using BaseKeyAction = BasicBaseKeyAction<>;
}

#include "BasicBaseKeyAction.inl"
