#include "lambdaPositioning.h"

namespace ui {
	LambdaPositioning::LambdaPositioning(float (*findPosition)(float, float, float, float)) : positioning(findPosition) {}
	
	float LambdaPositioning::findPosition(float parentPosition, float objectSize, float parentSize, float targetSize) {
		return positioning(parentPosition, objectSize, parentSize, targetSize);
	}
	
	LambdaPositioning *LambdaPositioning::copy() {
		return new LambdaPositioning{positioning};
	}
}