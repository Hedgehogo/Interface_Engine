#include "ParentCoefficientSizing.hpp"

namespace ie {
	ParentCoefficientSizing::Make::Make(float coefficient, float addition) :
		coefficient(coefficient), addition(addition) {
	}
	
	ParentCoefficientSizing* ParentCoefficientSizing::Make::make(float normal_size) {
		return new ParentCoefficientSizing{std::move(*this), normal_size};
	}
	
	ParentCoefficientSizing::ParentCoefficientSizing(Make&& make, float) :
		coefficient(make.coefficient), addition(make.addition) {
	}
	
	ParentCoefficientSizing::ParentCoefficientSizing(float coefficient, float addition) : coefficient(coefficient), addition(addition) {
	}
	
	void ParentCoefficientSizing::init(float) {
	}
	
	float ParentCoefficientSizing::find_size(float parent_size, float) {
		return parent_size * coefficient + addition;
	}
	
	ParentCoefficientSizing* ParentCoefficientSizing::copy() {
		return new ParentCoefficientSizing{*this};
	}
	
	float ParentCoefficientSizing::get_parent_size(float object_size) {
		return (object_size - addition) / coefficient;
	}
	
	bool DecodePointer<ParentCoefficientSizing>::decode_pointer(const YAML::Node& node, ParentCoefficientSizing*& parent_coefficient_sizing) {
		parent_coefficient_sizing = new ParentCoefficientSizing{
			node["coefficient"].as<float>(),
			conv_def(node["addition"], 0.f)
		};
		return true;
	}
}