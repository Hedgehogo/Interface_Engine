#include "TargetCoefficientSizing.hpp"

namespace ie {
	TargetCoefficientSizing::Make::Make(float coefficient, float addition) :
		coefficient(coefficient), addition(addition) {
	}
	
	TargetCoefficientSizing* TargetCoefficientSizing::Make::make(float normal_size) {
		return new TargetCoefficientSizing{std::move(*this), normal_size};
	}
	
	TargetCoefficientSizing::TargetCoefficientSizing(Make&& make, float) :
		coefficient_(make.coefficient), addition_(make.addition) {
	}
	
	TargetCoefficientSizing::TargetCoefficientSizing(float coefficient, float addition) : coefficient_(coefficient), addition_(addition) {
	}
	
	void TargetCoefficientSizing::init(float) {
	}
	
	float TargetCoefficientSizing::find_size(float, float target_size) {
		return target_size * coefficient_ + addition_;
	}
	
	TargetCoefficientSizing* TargetCoefficientSizing::copy() {
		return new TargetCoefficientSizing{*this};
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<TargetCoefficientSizing>::decode_pointer(const YAML::Node& node, TargetCoefficientSizing*& target_coefficient_sizing) {
		target_coefficient_sizing = new TargetCoefficientSizing{
			node["coefficient"].as<float>(),
			conv_def(node["addition"], 0.f)
		};
		return true;

	}
	*/
}