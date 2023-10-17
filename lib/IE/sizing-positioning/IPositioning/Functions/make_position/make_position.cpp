#include "make_position.hpp"
#include <utility>

namespace ie {
	IPositioning* make_position(float coefficient, float offset, bool relativeTarget) {
		if(!relativeTarget) {
			return new InternalPositioning{coefficient, offset};
		}
		return new InternalTargetPositioning{coefficient, offset};
	}
	
	IPositioning* make_position(float coefficient, float objectCoefficient, float offset, bool relativeTarget) {
		if(!relativeTarget) {
			return new MatchPositioning{coefficient, objectCoefficient, offset};
		}
		return new MatchTargetPositioning{coefficient, objectCoefficient, offset};
	}
	
	IPositioning* make_position(Location parentSide, Location objectSide, float offset) {
		return new MatchSidesPositioning{parentSide, objectSide, offset};
	}
	
	IPositioning* make_position(FnPositioning::FindPositionFn findPositionFn) {
		return new FnPositioning{std::move(findPositionFn)};
	}
}