#pragma once
#include <SFML/Graphics/RenderTarget.hpp>

namespace ui {
	class Sizing {
	public:
		Sizing() = default;
		
		virtual ~Sizing() = default;
		
		virtual void init(float normalSize) = 0;
		
		virtual float findSize(float parentSize, float targetSize) = 0;
		
		float operator()(float parentSize, float targetSize);
		
		virtual float getParentMinSize(float objectMinSize);
		
		virtual Sizing* copy() = 0;
	};
}
