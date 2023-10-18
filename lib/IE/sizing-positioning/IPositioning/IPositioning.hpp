#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"

namespace ie {
	class IPositioning {
	public:
		IPositioning() = default;
		
		virtual ~IPositioning() = default;
		
		virtual float find_position(float parent_position, float object_size, float parent_size, float target_size) = 0;
		
		float operator()(float parent_position, float object_size, float parent_size, float target_size);
		
		virtual IPositioning* copy() = 0;
	};
}