#include "iPositioning2.hpp"

namespace ui {
	sf::Vector2f IPositioning2::operator()(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) {
		return this->findPosition(parentPosition, parentSize, objectSize);
	}
	
/*	Positioning *makePosition(float coefficient, float offset, bool relativeTarget) {
		if(!relativeTarget) {
			return new InternalPositioning{coefficient, offset};
		}
		return new InternalTargetPositioning{coefficient, offset};
	}
	
	Positioning *makePosition(float coefficient, float objectCoefficient, float offset, bool relativeTarget) {
		if(!relativeTarget) {
			return new MatchPositioning{coefficient, objectCoefficient, offset};
		}
		return new MatchTargetPositioning{coefficient, objectCoefficient, offset};
	}*/
}