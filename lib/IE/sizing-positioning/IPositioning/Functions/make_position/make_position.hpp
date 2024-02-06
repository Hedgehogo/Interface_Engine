#pragma once

#include "../../IPositioning.hpp"
#include "../../InternalPositioning/InternalPositioning.hpp"
#include "../../InternalTargetPositioning/InternalTargetPositioning.hpp"
#include "../../MatchPositioning/MatchPositioning.hpp"
#include "../../MatchSidesPositioning/MatchSidesPositioning.hpp"
#include "../../MatchTargetPositioning/MatchTargetPositioning.hpp"
#include "IE/sizing-positioning/IPositioning/FnPositioning/FnPositioning.hpp"

namespace ie {
	IPositioning* make_position(float coefficient, float offset, bool relative_target = false);
	
	IPositioning* make_position(float coefficient, float object_coefficient, float offset, bool relative_target = false);
	
	IPositioning* make_position(Location parent_side, Location object_side, float offset);
	
	IPositioning* make_position(FnPositioning::FindPositionFn find_position_fn);
}