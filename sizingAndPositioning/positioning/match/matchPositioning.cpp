#include "matchPositioning.h"

namespace ui {
	MatchPositioning::MatchPositioning(float parentCoefficient, float objectCoefficient, float offset) : parentCoefficient(parentCoefficient), objectCoefficient(objectCoefficient), offset(offset) {}
	
	void MatchPositioning::init(sf::RenderTarget &) {}
	
	float MatchPositioning::findPosition(float parentPosition, float parentSize, float objectSize) {
		return parentPosition + parentSize * parentCoefficient - objectSize * objectCoefficient + offset;
	}
	
	MatchPositioning *MatchPositioning::copy() {
		return new MatchPositioning{parentCoefficient, objectCoefficient, offset};
	}
	
	Positioning *createPosition(float parentCoefficient, float objectCoefficient, float offset) {
		return new MatchPositioning{parentCoefficient, objectCoefficient, offset};
	}
}