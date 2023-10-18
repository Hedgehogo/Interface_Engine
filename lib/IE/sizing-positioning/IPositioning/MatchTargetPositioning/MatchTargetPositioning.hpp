#pragma once

#include "../IPositioning.hpp"

namespace ie {
	class MatchTargetPositioning : public virtual IPositioning {
	public:
		MatchTargetPositioning(float target_coefficient, float object_coefficient, float offset = 0);
		
		float find_position(float, float object_size, float, float target_size) override;
		
		MatchTargetPositioning* copy() override;
	
	protected:
		float target_coefficient;
		float object_coefficient;
		float offset;
	};
	
	template<>
	struct DecodePointer<MatchTargetPositioning> {
		static bool decode_pointer(const YAML::Node& node, MatchTargetPositioning*& match_target_positioning);
	};
}