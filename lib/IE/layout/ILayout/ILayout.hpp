#pragma once

#include "SFML/Graphics.hpp"

namespace ie {
	struct LayoutData {
		sf::Vector2f position{};
		sf::Vector2f size{};
		
		LayoutData();
		
		LayoutData(sf::Vector2f position, sf::Vector2f size);
		
		void set_position(sf::Vector2f position);
		
		void move(sf::Vector2f position);
		
		void set_size(sf::Vector2f size);
		
		void resize(sf::Vector2f size, sf::Vector2f position);
	};
	
	class ILayout {
	public:
		virtual const LayoutData& layout_get_data() const = 0;
		
	protected:
		virtual LayoutData& layout_get_data() = 0;
	};
}
