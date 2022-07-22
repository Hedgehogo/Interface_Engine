#pragma once
#include "../../positioning.h"

namespace ui {
	class InternalTargetPositioning : public Positioning {
	protected:
		float coefficient;
		float offset;
	
	public:
		explicit InternalTargetPositioning(float coefficient, float offset = 0);
		
		float findPosition(float parentPosition, float objectSize, float, float targetSize) override;
		
		InternalTargetPositioning* copy() override;
	};
}
