#include "parentCoefficientSizing.hpp"

namespace ui {
	ParentCoefficientSizing::ParentCoefficientSizing(float coefficient, float addition) : coefficient(coefficient), addition(addition) {
	}
	
	void ParentCoefficientSizing::init(float) {
	}
	
	float ParentCoefficientSizing::findSize(float parentSize, float) {
		return parentSize * coefficient + addition;
	}
	
	ParentCoefficientSizing* ParentCoefficientSizing::copy() {
		return new ParentCoefficientSizing{*this};
	}
	
	float ParentCoefficientSizing::getParentSize(float objectSize) {
		return (objectSize - addition) / coefficient;
	}
	
	bool DecodePointer<ParentCoefficientSizing>::decodePointer(const YAML::Node& node, ParentCoefficientSizing*& parentCoefficientSizing) {
		parentCoefficientSizing = new ParentCoefficientSizing{
			node["coefficient"].as<float>(),
			convDef(node["addition"], 0.f)
		};
		return true;
	}
}