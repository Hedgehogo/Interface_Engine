#include "make_position.hpp"
#include <utility>

namespace ie {
	IPositioning* make_position(float coefficient, float offset, bool relative_target) {
		if(!relative_target) {
			return new InternalPositioning{coefficient, offset};
		}
		return new InternalTargetPositioning{coefficient, offset};
	}
	
	IPositioning* make_position(float coefficient, float object_coefficient, float offset, bool relative_target) {
		if(!relative_target) {
			return new MatchPositioning{coefficient, object_coefficient, offset};
		}
		return new MatchTargetPositioning{coefficient, object_coefficient, offset};
	}
	
	IPositioning* make_position(Location parent_side, Location object_side, float offset) {
		return new MatchSidesPositioning{parent_side, object_side, offset};
	}
	
	IPositioning* make_position(FnPositioning::FindPositionFn find_position_fn) {
		return new FnPositioning{std::move(find_position_fn)};
	}
}