#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

namespace ie {
	class IPositioning {
	public:
		IPositioning() = default;
		
		virtual ~IPositioning() = default;
		
		virtual auto find_position(float parent_position, float object_size, float parent_size, float target_size) -> float = 0;
		
		virtual auto copy() -> IPositioning* = 0;
		
		auto operator()(float parent_position, float object_size, float parent_size, float target_size) -> float;
	};
}