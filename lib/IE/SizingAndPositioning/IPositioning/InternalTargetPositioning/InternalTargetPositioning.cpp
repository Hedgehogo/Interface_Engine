#include "InternalTargetPositioning.hpp"

namespace ui {
	InternalTargetPositioning::InternalTargetPositioning(float coefficient, float offset) : coefficient(coefficient), offset(offset) {
	}
	
	float InternalTargetPositioning::findPosition(float, float objectSize, float, float targetSize) {
		return (targetSize - objectSize) * coefficient + offset;
	}
	
	InternalTargetPositioning* InternalTargetPositioning::copy() {
		return new InternalTargetPositioning{*this};
	}
	
	float InternalTargetPositioning::getCoefficient() const {
		return coefficient;
	}
	
	float InternalTargetPositioning::getOffset() const {
		return offset;
	}
	
	bool DecodePointer<InternalTargetPositioning>::decodePointer(const YAML::Node& node, InternalTargetPositioning*& internalTargetPositioning) {
		internalTargetPositioning = new InternalTargetPositioning{
			node["coefficient"].as<float>(),
			convDef(node["offset"], 0.f)
		};
		return true;
	}
}