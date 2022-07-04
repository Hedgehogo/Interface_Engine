#include "internalPositioning.h"

namespace ui {
	InternalPositioning::InternalPositioning(float coefficient, float offset) : coefficient(coefficient), offset(offset) {}
	
	float InternalPositioning::findPosition(float parentPosition, float objectSize, float parentSize, float) {
		return parentPosition + (parentSize - objectSize) * coefficient + offset;
	}
	
	InternalPositioning *InternalPositioning::copy() {
		return new InternalPositioning{coefficient, offset};
	}
}