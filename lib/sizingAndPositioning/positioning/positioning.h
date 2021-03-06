#pragma once
#include <SFML/Graphics/RenderTarget.hpp>

namespace ui {
	class Positioning {
	public:
		Positioning() = default;
		
		virtual ~Positioning() = default;
		
		virtual float findPosition(float parentPosition, float objectSize, float parentSize, float targetSize) = 0;
		
		float operator()(float parentPosition, float objectSize, float parentSize, float targetSize);
		
		virtual Positioning* copy() = 0;
	};
}
