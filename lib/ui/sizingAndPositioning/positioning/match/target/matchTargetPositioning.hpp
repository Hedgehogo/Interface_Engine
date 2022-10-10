#pragma once
#include "../../positioning.hpp"

namespace ui {
	class MatchTargetPositioning : public Positioning {
	protected:
		float targetCoefficient;
		float objectCoefficient;
		float offset;
	
	public:
		MatchTargetPositioning(float targetCoefficient, float objectCoefficient, float offset = 0);
		
		float findPosition(float parentPosition, float objectSize, float, float targetSize) override;
		
		MatchTargetPositioning* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, MatchTargetPositioning *&matchTargetPositioning);
}
