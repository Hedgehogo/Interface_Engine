#include "matchTargetPositioning.h"

namespace ui {
	MatchTargetPositioning::MatchTargetPositioning(float targetCoefficient, float objectCoefficient, float offset) : targetCoefficient(targetCoefficient), objectCoefficient(objectCoefficient), offset(offset) {}
	
	float MatchTargetPositioning::findPosition(float parentPosition, float objectSize, float, float targetSize) {
		return parentPosition + targetSize * targetCoefficient - objectSize * objectCoefficient + offset;
	}
	
	MatchTargetPositioning *MatchTargetPositioning::copy() {
		return new MatchTargetPositioning{targetCoefficient, objectCoefficient, offset};
	}
}