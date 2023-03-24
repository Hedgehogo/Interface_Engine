#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include "../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class ISizing {
	public:
		ISizing() = default;
		
		virtual ~ISizing() = default;
		
		virtual void init(float normalSize) = 0;
		
		virtual float findSize(float parentSize, float targetSize) = 0;
		
		float operator()(float parentSize, float targetSize);
		
		virtual float getParentSize(float objectSize);
		
		virtual ISizing* copy() = 0;
	};
}
