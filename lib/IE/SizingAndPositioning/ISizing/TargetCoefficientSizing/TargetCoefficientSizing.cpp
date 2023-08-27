#include "TargetCoefficientSizing.hpp"

namespace ie {
	TargetCoefficientSizing::Make::Make(float coefficient, float addition) :
		coefficient(coefficient), addition(addition) {
	}
	
	TargetCoefficientSizing* TargetCoefficientSizing::Make::make(float normalSize) {
		return new TargetCoefficientSizing{std::move(*this), normalSize};
	}
	
	TargetCoefficientSizing::TargetCoefficientSizing(Make&& make, float) :
		coefficient(make.coefficient), addition(make.addition) {
	}
	
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