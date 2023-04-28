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

	
	bool DecodePointer<InternalPositioning>::decodePointer(const YAML::Node &node, InternalPositioning *&internalPositioning) {
		if(node.IsScalar()) {
			internalPositioning = new InternalPositioning{
				node.as<float>()
			};
		} else {
			internalPositioning = new InternalPositioning{
				node["coefficient"].as<float>(),
				convDef(node["offset"], 0.f)
			};
		}
		return true;
	}
}