#include "makePositioning.hpp"
#include <utility>

namespace ui {
	IPositioning* makePosition(float coefficient, float offset, bool relativeTarget) {
		if(!relativeTarget) {
			return new InternalPositioning{coefficient, offset};
		}
		return new InternalTargetPositioning{coefficient, offset};
	}
	
	IPositioning* makePosition(float coefficient, float objectCoefficient, float offset, bool relativeTarget) {
		if(!relativeTarget) {
			return new MatchPositioning{coefficient, objectCoefficient, offset};
		}
		return new MatchTargetPositioning{coefficient, objectCoefficient, offset};
	}
	
	IPositioning* makePosition(Location parentSide, Location objectSide, float offset) {
		return new MatchSidesPositioning{parentSide, objectSide, offset};
	}
	
	IPositioning* makePosition(LambdaPositioning::FindPositionFunc findPosition) {
		return new LambdaPositioning{std::move(findPosition)};
	}
}