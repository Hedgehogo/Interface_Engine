#pragma once

#include "../IPositioning.hpp"

namespace ui {
	class MatchTargetPositioning : public IPositioning {
	public:
		MatchTargetPositioning(float targetCoefficient, float objectCoefficient, float offset = 0);
		
		float findPosition(float, float objectSize, float, float targetSize) override;
		
		MatchTargetPositioning* copy() override;
	
	protected:
		float targetCoefficient;
		float objectCoefficient;
		float offset;
	};
	
	template<>
	struct DecodePointer<MatchTargetPositioning> {
		static bool decodePointer(const YAML::Node& node, MatchTargetPositioning*& matchTargetPositioning);
	};
}
