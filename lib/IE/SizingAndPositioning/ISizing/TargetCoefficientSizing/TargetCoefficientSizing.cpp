#include "TargetCoefficientSizing.hpp"

namespace ui {
	TargetCoefficientSizing::TargetCoefficientSizing(float coefficient, float addition) : coefficient(coefficient), addition(addition) {
	}
	
	void TargetCoefficientSizing::init(float) {
	}
	
	float TargetCoefficientSizing::findSize(float, float targetSize) {
		return targetSize * coefficient + addition;
	}
	
	TargetCoefficientSizing* TargetCoefficientSizing::copy() {
		return new TargetCoefficientSizing{*this};
	}
	
	bool DecodePointer<TargetCoefficientSizing>::decodePointer(const YAML::Node& node, TargetCoefficientSizing*& targetCoefficientSizing) {
		targetCoefficientSizing = new TargetCoefficientSizing{
			node["coefficient"].as<float>(),
			convDef(node["addition"], 0.f)
		};
		return true;
	}
}