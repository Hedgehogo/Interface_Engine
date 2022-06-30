#pragma once
#include <SFML/Graphics/RenderTarget.hpp>

namespace ui {
	class Positioning {
	public:
		Positioning() = default;
		
		virtual ~Positioning() = default;
		
		virtual void init(sf::RenderTarget& renderTarget) = 0;
		
		virtual float findPosition(float parentPosition, float parentSize, float objectSize) = 0;
		
		float operator()(float parentPosition, float parentSize, float objectSize);
		
		virtual Positioning* copy() = 0;
	};
}
