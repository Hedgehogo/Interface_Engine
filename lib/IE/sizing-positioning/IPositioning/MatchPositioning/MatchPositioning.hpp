#pragma once

#include "../IPositioning.hpp"

namespace ie {
	class MatchPositioning : public virtual IPositioning {
	public:
		MatchPositioning(float parent_coefficient, float object_coefficient, float offset = 0);
		
		float find_position(float parent_position, float object_size, float parent_size, float) override;
		
		MatchPositioning* copy() override;
	
	protected:
		float parent_coefficient;
		float object_coefficient;
		float offset;
	};
	
	template<>
	struct DecodePointer<MatchPositioning> {
		static bool decode_pointer(const YAML::Node& node, MatchPositioning*& match_positioning);
	};
}
