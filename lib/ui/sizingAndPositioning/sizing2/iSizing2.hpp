#pragma once
#include <SFML/Graphics/RenderTarget.hpp>

namespace ui {
	class ISizing2 {
	public:
		virtual ~ISizing2() = default;
		
		virtual void init(sf::RenderTarget& renderTarget, sf::Vector2f normalSize) = 0;
		
		virtual sf::Vector2f findSize(sf::Vector2f parentSize) = 0;
		
		virtual sf::Vector2f getParentSize(sf::Vector2f objectSize) = 0;
		
		virtual sf::Vector2f operator()(sf::Vector2f parentSize);
		
		virtual ISizing2* copy() = 0;
	};
}
