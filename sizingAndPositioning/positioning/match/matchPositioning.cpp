#include "matchPositioning.h"

namespace ui {
	MatchPositioning::MatchPositioning(float parentCoefficient, float objectCoefficient, float offset) : parentCoefficient(parentCoefficient), objectCoefficient(objectCoefficient), offset(offset) {}
	
	float MatchPositioning::findPosition(float parentPosition, float objectSize, float parentSize, float targetSize) {
		return parentPosition + parentSize * parentCoefficient - objectSize * objectCoefficient + offset;
	}
	
	MatchPositioning *MatchPositioning::copy() {
		return new MatchPositioning{parentCoefficient, objectCoefficient, offset};
	}
}