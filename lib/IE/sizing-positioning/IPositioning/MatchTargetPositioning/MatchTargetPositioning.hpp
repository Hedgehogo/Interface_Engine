#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../IPositioning.hpp"

namespace ie {
	class MatchTargetPositioning : public virtual IPositioning {
	public:
		MatchTargetPositioning(float target_coefficient, float object_coefficient, float offset = 0);
		
		auto find_position(float, float object_size, float, float target_size) -> float override;
		
		auto copy() -> MatchTargetPositioning* override;
	
	protected:
		float target_coefficient_;
		float object_coefficient_;
		float offset_;
	};
}

template<>
struct ieml::Decode<char, ie::MatchTargetPositioning> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::MatchTargetPositioning>;
};
