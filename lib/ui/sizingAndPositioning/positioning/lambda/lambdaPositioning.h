#pragma once
#include "../positioning.hpp"

namespace ui {
	class LambdaPositioning : public Positioning {
	protected:
		float (*positioning)(float parentPosition, float objectSize, float parentSize, float targetSize);
		
	public:
		explicit LambdaPositioning(float (*findPosition)(float parentPosition, float objectSize, float parentSize, float targetSize));
		
		float findPosition(float parentPosition, float objectSize, float parentSize, float targetSize) override;
		
		LambdaPositioning* copy() override;
	};
}
