#include "LambdaPositioning.hpp"
#include <utility>

namespace ui {
	LambdaPositioning::LambdaPositioning(FindPositionFunc findPositionFunc) : findPositionFunc(std::move(findPositionFunc)) {
	}
	
	float LambdaPositioning::findPosition(float parentPosition, float objectSize, float parentSize, float targetSize) {
		return findPositionFunc(parentPosition, objectSize, parentSize, targetSize);
	}
	
	LambdaPositioning* LambdaPositioning::copy() {
		return new LambdaPositioning{findPositionFunc};
	}
}