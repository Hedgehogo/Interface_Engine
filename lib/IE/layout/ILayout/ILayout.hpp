#pragma once

#include "SFML/Graphics.hpp"

namespace ie {
	struct LayoutData {
		sf::Vector2f position{};
		sf::Vector2f size{};
		
		LayoutData();
		
		LayoutData(sf::Vector2f position, sf::Vector2f size);
		
		auto set_position(sf::Vector2f position) -> void;
		
		auto move(sf::Vector2f offset) -> void;
		
		auto set_size(sf::Vector2f size) -> void;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void;
	};
	
	class ILayout {
	public:
		virtual auto layout_get_data() const -> LayoutData const& = 0;
		
	protected:
		virtual auto layout_get_data() -> LayoutData& = 0;
	};
}
