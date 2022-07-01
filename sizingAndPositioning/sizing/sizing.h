#pragma once
#include <SFML/Graphics/RenderTarget.hpp>

namespace ui {
	class Sizing {
	public:
		Sizing() = default;
		
		virtual ~Sizing() = default;
		
		virtual void init(sf::RenderTarget& renderTarget, float normalSize) = 0;
		
		virtual float findSize(float parentSize) = 0;
		
		float operator()(float parentSize);
		
		virtual Sizing* copy() = 0;
	};
}
