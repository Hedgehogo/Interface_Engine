#include "targetCoefficientSizing.hpp"

namespace ui {
	TargetCoefficientSizing::TargetCoefficientSizing(float coefficient, float addition) : coefficient(coefficient), addition(addition) {
	}
	
	void TargetCoefficientSizing::init(float) {
	}
	
	float TargetCoefficientSizing::findSize(float, float targetSize) {
		return targetSize * coefficient + addition;
	}
	
	TargetCoefficientSizing* TargetCoefficientSizing::copy() {
		return new TargetCoefficientSizing{coefficient, addition};
	}
	
	bool DecodePointer<TargetCoefficientSizing>::decodePointer(const YAML::Node& node, TargetCoefficientSizing*& targetCoefficientSizing) {
		float coefficient;
		float addition{0.f};
		
		node["coefficient"] >> coefficient;
		if(node["addition"])
			node["addition"] >> addition;
		
		{
			targetCoefficientSizing = new TargetCoefficientSizing{coefficient, addition};
			return true;
		}
	}
}