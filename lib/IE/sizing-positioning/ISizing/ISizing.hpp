#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	class ISizing {
	public:
		struct Make {
			virtual auto make(float normal_size) -> ISizing* = 0;
			
			virtual ~Make() = default;
		};
		
		ISizing() = default;
		
		virtual auto find_size(float parent_size, float target_size) -> float = 0;
		
		virtual auto get_parent_size(float object_min_size) -> float;
		
		auto operator()(float parent_size, float target_size) -> float;
		
		virtual ~ISizing() = default;
	};
}