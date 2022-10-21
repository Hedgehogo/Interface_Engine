#include "internalPositioning.hpp"

namespace ui {
	InternalPositioning::InternalPositioning(float coefficient, float offset) : coefficient(coefficient), offset(offset) {}
	
	float InternalPositioning::findPosition(float parentPosition, float objectSize, float parentSize, float) {
		return parentPosition + (parentSize - objectSize) * coefficient + offset;
	}
	
	InternalPositioning *InternalPositioning::copy() {
		return new InternalPositioning{coefficient, offset};
	}

	float InternalPositioning::getCoefficient() const {
		return coefficient;
	}

	float InternalPositioning::getOffset() const {
		return offset;
	}

	bool convertPointer(const YAML::Node &node, InternalPositioning *&internalPositioning) {
		float coefficient;
		float offset{0.f};
		
		node["coefficient"] >> coefficient;
		if(node["offset"])
			node["offset"] >> offset;
		
		{ internalPositioning = new InternalPositioning{coefficient, offset}; return true; }
	}
}