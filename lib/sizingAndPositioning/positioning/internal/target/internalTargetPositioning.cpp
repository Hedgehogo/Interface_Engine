#include "internalTargetPositioning.h"

namespace ui {
	InternalTargetPositioning::InternalTargetPositioning(float coefficient, float offset) : coefficient(coefficient), offset(offset) {}
	
	float InternalTargetPositioning::findPosition(float parentPosition, float objectSize, float, float targetSize) {
		return (targetSize - objectSize) * coefficient + offset;
	}
	
	InternalTargetPositioning *InternalTargetPositioning::copy() {
		return new InternalTargetPositioning{coefficient, offset};
	}
}