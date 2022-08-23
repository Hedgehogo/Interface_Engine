#include "parentCoefficientSizing.hpp"

namespace ui {
	
	ParentCoefficientSizing::ParentCoefficientSizing(float coefficient, float addition) : coefficient(coefficient), addition(addition) {}
	
	void ParentCoefficientSizing::init(float) {}
	
	float ParentCoefficientSizing::findSize(float parentSize, float) {
		return parentSize * coefficient + addition;
	}
	
	ParentCoefficientSizing *ParentCoefficientSizing::copy() {
		return new ParentCoefficientSizing{coefficient, addition};
	}
	
	float ParentCoefficientSizing::getParentSize(float objectSize) {
		return (objectSize - addition) / coefficient;
	}
	
	ParentCoefficientSizing *ParentCoefficientSizing::createFromYaml(const YAML::Node &node) {
		float coefficient;
		float addition{0.f};
		
		node["coefficient"] >> coefficient;
		if(node["addition"])
			node["addition"] >> addition;
		
		return new ParentCoefficientSizing{coefficient, addition};
	}
}