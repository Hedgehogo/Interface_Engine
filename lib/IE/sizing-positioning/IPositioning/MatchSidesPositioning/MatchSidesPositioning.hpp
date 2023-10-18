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
		Location parent_side;
		Location object_side;
		float offset;
	};
	
	template<>
	struct DecodePointer<MatchSidesPositioning> {
		static bool decode_pointer(const YAML::Node& node, MatchSidesPositioning*& match_sides_positioning);
	};
}