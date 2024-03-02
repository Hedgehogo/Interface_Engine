#pragma once

#include "../IPositioning.hpp"
#include "IE/enums/Location/Location.hpp"

namespace ie {
	class MatchSidesPositioning : public virtual IPositioning {
	public:
		MatchSidesPositioning(Location parent_side, Location object_side, float offset = 0);
		
		auto find_position(float parent_position, float object_size, float parent_size, float) -> float override;
		
		auto copy() -> MatchSidesPositioning* override;
	
	protected:
		Location parent_side_;
		Location object_side_;
		float offset_;
	};
}

template<>
struct ieml::Decode<char, ie::MatchSidesPositioning> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::MatchSidesPositioning>;
};
