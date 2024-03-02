#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../IPositioning.hpp"

namespace ie {
	class MatchPositioning : public virtual IPositioning {
	public:
		MatchPositioning(float parent_coefficient, float object_coefficient, float offset = 0);
		
		auto find_position(float parent_position, float object_size, float parent_size, float) -> float override;
		
		auto copy() -> MatchPositioning* override;
	
	protected:
		float parent_coefficient_;
		float object_coefficient_;
		float offset_;
	};
}

template<>
struct ieml::Decode<char, ie::MatchPositioning> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::MatchPositioning>;
};
