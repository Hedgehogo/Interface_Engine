#pragma once

#include "../IPositioning.hpp"
#include "IE/enums/Location/Location.hpp"

namespace ie {
	class MatchSidesPositioning : public virtual IPositioning {
	public:
		MatchSidesPositioning(Location parent_side, Location object_side, float offset = 0);
		
		float find_position(float parent_position, float object_size, float parent_size, float) override;
		
		MatchSidesPositioning* copy() override;
	
	protected:
		Location parent_side_;
		Location object_side_;
		float offset_;
	};
}

template<>
struct ieml::Decode<char, ie::MatchSidesPositioning> {
	static orl::Option<ie::MatchSidesPositioning> decode(ieml::Node const& node);
};
