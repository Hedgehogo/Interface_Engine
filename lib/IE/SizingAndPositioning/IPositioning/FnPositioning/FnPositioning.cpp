#include "FnPositioning.hpp"
#include <utility>

namespace ie {
	FnPositioning::FnPositioning(FindPositionFn findPositionFn) : findPositionFn(std::move(findPositionFn)) {
	}
	
	float FnPositioning::findPosition(float parentPosition, float objectSize, float parentSize, float targetSize) {
		return findPositionFn(parentPosition, objectSize, parentSize, targetSize);
	}
	
	FnPositioning* FnPositioning::copy() {
		return new FnPositioning{findPositionFn};
	}
}