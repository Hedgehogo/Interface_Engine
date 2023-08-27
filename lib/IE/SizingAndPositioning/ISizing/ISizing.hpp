#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "../../Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class ISizing {
	public:
		struct Make {
			virtual ISizing* make(float normalSize) = 0;
			
			virtual ~Make() = default;
		};
		
		ISizing() = default;
		
		virtual ~ISizing() = default;
		
		virtual void init(float normalSize) = 0;
		
		virtual float findSize(float parentSize, float targetSize) = 0;
		
		float operator()(float parentSize, float targetSize);
		
		virtual float getParentSize(float objectMinSize);
		
		virtual ISizing* copy() = 0;
	};
}
