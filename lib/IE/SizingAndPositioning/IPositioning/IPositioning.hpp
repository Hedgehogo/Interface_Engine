#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "../../Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class IPositioning {
	public:
		IPositioning() = default;
		
		virtual ~IPositioning() = default;
		
		virtual float findPosition(float parentPosition, float objectSize, float parentSize, float targetSize) = 0;
		
		float operator()(float parentPosition, float objectSize, float parentSize, float targetSize);
		
		virtual IPositioning* copy() = 0;
	};
}
