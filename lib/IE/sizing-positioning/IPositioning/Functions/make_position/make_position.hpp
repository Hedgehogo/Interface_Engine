#pragma once

#include "../../IPositioning.hpp"
#include "../../InternalPositioning/InternalPositioning.hpp"
#include "../../InternalTargetPositioning/InternalTargetPositioning.hpp"
#include "../../MatchPositioning/MatchPositioning.hpp"
#include "../../MatchSidesPositioning/MatchSidesPositioning.hpp"
#include "../../MatchTargetPositioning/MatchTargetPositioning.hpp"
#include "IE/sizing-positioning/IPositioning/FnPositioning/FnPositioning.hpp"

namespace ie {
	auto make_position(float coefficient, float offset, bool relative_target = false) -> IPositioning*;
	
	auto make_position(float coefficient, float object_coefficient, float offset, bool relative_target = false) -> IPositioning*;
	
	auto make_position(Location parent_side, Location object_side, float offset) -> IPositioning*;
	
	auto make_position(FnPositioning::FindPositionFn find_position_fn) -> IPositioning*;
}