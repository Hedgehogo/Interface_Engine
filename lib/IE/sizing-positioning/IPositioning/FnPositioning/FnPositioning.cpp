#include "FnPositioning.hpp"
#include <utility>

namespace ie {
	FnPositioning::FnPositioning(FindPositionFn find_position_fn) : find_position_fn_(std::move(find_position_fn)) {
	}
	
	float FnPositioning::find_position(float parent_position, float object_size, float parent_size, float target_size) {
		return find_position_fn_(parent_position, object_size, parent_size, target_size);
	}
	
	FnPositioning* FnPositioning::copy() {
		return new FnPositioning{find_position_fn_};
	}
}