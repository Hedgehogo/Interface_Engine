#include "internalTargetPositioning.hpp"

namespace ui {
	InternalTargetPositioning::InternalTargetPositioning(float coefficient, float offset) : coefficient(coefficient), offset(offset) {
	}
	
	float InternalTargetPositioning::findPosition(float parentPosition, float objectSize, float, float targetSize) {
		return (targetSize - objectSize) * coefficient + offset;
	}
	
	InternalTargetPositioning* InternalTargetPositioning::copy() {
		return new InternalTargetPositioning{coefficient, offset};
	}
	
	float InternalTargetPositioning::getCoefficient() const {
		return coefficient;
	}
	
	float InternalTargetPositioning::getOffset() const {
		return offset;
	}
	
	bool DecodePointer<InternalTargetPositioning>::decodePointer(const YAML::Node& node, InternalTargetPositioning*& internalTargetPositioning) {
		float coefficient;
		float offset{0.f};
		
		node["coefficient"] >> coefficient;
		if(node["offset"])
			node["offset"] >> offset;
		
		{
			internalTargetPositioning = new InternalTargetPositioning{coefficient, offset};
			return true;
		}
	}
}