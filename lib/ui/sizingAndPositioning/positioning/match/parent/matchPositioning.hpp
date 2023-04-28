#pragma once

#include "../../iPositioning.hpp"

namespace ui {
	class MatchPositioning : public IPositioning {
	protected:
		float parentCoefficient;
		float objectCoefficient;
		float offset;
	
	public:
		MatchPositioning(float parentCoefficient, float objectCoefficient, float offset = 0);
		
		float findPosition(float parentPosition, float objectSize, float parentSize, float targetSize) override;
		
		MatchPositioning* copy() override;
	};
	
	
	template<>
	struct DecodePointer<MatchPositioning> {
		static bool decodePointer(const YAML::Node& node, MatchPositioning*& matchPositioning);
	};
}
