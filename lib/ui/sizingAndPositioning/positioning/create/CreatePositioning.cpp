#include "CreatePositioning.hpp"

namespace ui {
	Positioning *createPosition(float coefficient, float offset, bool relativeTarget) {
		if(!relativeTarget) {
			return new InternalPositioning{coefficient, offset};
		}
		return new InternalTargetPositioning{coefficient, offset};
	}

	Positioning *createPosition(float coefficient, float objectCoefficient, float offset, bool relativeTarget) {
		if(!relativeTarget) {
			return new MatchPositioning{coefficient, objectCoefficient, offset};
		}
		return new MatchTargetPositioning{coefficient, objectCoefficient, offset};
	}

	Positioning *createPosition(Location parentSide, Location objectSide, float offset) {
		return new MatchSidesPositioning{parentSide, objectSide, offset};
	}
} // ui