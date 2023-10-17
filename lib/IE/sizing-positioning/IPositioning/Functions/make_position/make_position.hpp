#pragma once

#include "../../IPositioning.hpp"
#include "../../InternalPositioning/InternalPositioning.hpp"
#include "../../InternalTargetPositioning/InternalTargetPositioning.hpp"
#include "../../MatchPositioning/MatchPositioning.hpp"
#include "../../MatchSidesPositioning/MatchSidesPositioning.hpp"
#include "../../MatchTargetPositioning/MatchTargetPositioning.hpp"
#include "IE/sizing-positioning/IPositioning/FnPositioning/FnPositioning.hpp"

namespace ie {
	IPositioning* make_position(float coefficient, float offset, bool relativeTarget = false);
	
	IPositioning* make_position(float coefficient, float objectCoefficient, float offset, bool relativeTarget = false);
	
	IPositioning* make_position(Location parentSide, Location objectSide, float offset);
	
	IPositioning* make_position(FnPositioning::FindPositionFn findPositionFn);
}