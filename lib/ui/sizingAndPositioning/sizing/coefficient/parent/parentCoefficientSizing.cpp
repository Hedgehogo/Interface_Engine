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
	
	bool convertPointer(const YAML::Node &node, ParentCoefficientSizing *&parentCoefficientSizing) {
		float coefficient;
		float addition{0.f};
		
		node["coefficient"] >> coefficient;
		if(node["addition"])
			node["addition"] >> addition;
		
		{ parentCoefficientSizing = new ParentCoefficientSizing{coefficient, addition}; return true; }
	}
	
	bool DecodePointer<ParentCoefficientSizing>::decodePointer(const YAML::Node &node, ParentCoefficientSizing *&parentCoefficientSizing) {
		float coefficient;
		float addition{0.f};
		
		node["coefficient"] >> coefficient;
		if(node["addition"])
			node["addition"] >> addition;
		
		{ parentCoefficientSizing = new ParentCoefficientSizing{coefficient, addition}; return true; }
	}
}