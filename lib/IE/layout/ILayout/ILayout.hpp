#pragma once

#include "SFML/Graphics.hpp"

namespace ie {
	struct LayoutData {
		sf::Vector2f position{};
		sf::Vector2f size{};
		
		LayoutData();
		
		LayoutData(sf::Vector2f position, sf::Vector2f size);
		
		void setPosition(sf::Vector2f position);
		
		void move(sf::Vector2f position);
		
		void setSize(sf::Vector2f size);
		
		void resize(sf::Vector2f size, sf::Vector2f position);
	};
	
	class ILayout {
	public:
		virtual const LayoutData& layoutGetData() const = 0;
		
	protected:
		virtual LayoutData& layoutGetData() = 0;
	};
}
