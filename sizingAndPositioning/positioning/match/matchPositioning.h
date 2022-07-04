#pragma once
#include "../positioning.h"

namespace ui {
	class MatchPositioning : public Positioning {
	protected:
		float parentCoefficient;
		float objectCoefficient;
		float offset;
		
	public:
		MatchPositioning(float parentCoefficient, float objectCoefficient, float offset = 0);
		
		float findPosition(float parentPosition, float objectSize, float parentSize, float targetSize) override;
		
		MatchPositioning* copy() override;
	};
}
