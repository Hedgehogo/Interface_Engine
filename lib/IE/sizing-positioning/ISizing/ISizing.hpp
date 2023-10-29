#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	class ISizing {
	public:
		struct Make {
			virtual ISizing* make(float normal_size) = 0;
			
			virtual ~Make() = default;
		};
		
		ISizing() = default;
		
		virtual ~ISizing() = default;
		
		virtual void init(float normal_size) = 0;
		
		virtual float find_size(float parent_size, float target_size) = 0;
		
		float operator()(float parent_size, float target_size);
		
		virtual float get_parent_size(float object_min_size);
		
		virtual ISizing* copy() = 0;
	};
}