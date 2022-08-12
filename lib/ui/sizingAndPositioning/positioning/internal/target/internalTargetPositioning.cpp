#include "internalTargetPositioning.hpp"

namespace ui {
	InternalTargetPositioning::InternalTargetPositioning(float coefficient, float offset) : coefficient(coefficient), offset(offset) {}
	
	float InternalTargetPositioning::findPosition(float parentPosition, float objectSize, float, float targetSize) {
		return (targetSize - objectSize) * coefficient + offset;
	}
	
	InternalTargetPositioning *InternalTargetPositioning::copy() {
		return new InternalTargetPositioning{coefficient, offset};
	}
	
	InternalTargetPositioning *InternalTargetPositioning::createFromYaml(const YAML::Node &node) {
		float coefficient;
		float offset{0.f};
		
		node["coefficient"] >> coefficient;
		if(node["offset"])
			node["offset"] >> offset;
		
		return new InternalTargetPositioning{coefficient, offset};
	}
}