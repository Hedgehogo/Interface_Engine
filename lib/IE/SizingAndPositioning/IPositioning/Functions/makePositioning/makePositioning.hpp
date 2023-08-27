#pragma once

#include "../../IPositioning.hpp"
#include "../../InternalPositioning/InternalPositioning.hpp"
#include "../../InternalTargetPositioning/InternalTargetPositioning.hpp"
#include "../../MatchPositioning/MatchPositioning.hpp"
#include "../../MatchSidesPositioning/MatchSidesPositioning.hpp"
#include "../../MatchTargetPositioning/MatchTargetPositioning.hpp"
#include "../../LambdaPositioning/LambdaPositioning.hpp"

namespace ie {
	IPositioning* makePosition(float coefficient, float offset, bool relativeTarget = false);
	
	IPositioning* makePosition(float coefficient, float objectCoefficient, float offset, bool relativeTarget = false);
	
	IPositioning* makePosition(Location parentSide, Location objectSide, float offset);
	
	IPositioning* makePosition(LambdaPositioning::FindPositionFunc findPosition);
}