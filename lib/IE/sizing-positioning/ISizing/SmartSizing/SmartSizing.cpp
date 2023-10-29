#include "SmartSizing.hpp"

namespace ie {
	SmartSizing::Make::Make(float target_coefficient, float parent_coefficient, float addition) :
		target_coefficient(target_coefficient), parent_coefficient(parent_coefficient), addition(addition) {
	}
	
	SmartSizing* SmartSizing::Make::make(float normal_size) {
		return new SmartSizing{std::move(*this), normal_size};
	}
	
	SmartSizing::SmartSizing(Make&& make, float) :
		target_coefficient_(make.target_coefficient), parent_coefficient_(make.parent_coefficient), addition_(make.addition) {
	}
	
	SmartSizing::SmartSizing(float target_coefficient, float parent_coefficient, float addition) :
		target_coefficient_(target_coefficient), parent_coefficient_(parent_coefficient), addition_(addition) {
	}
	
	void SmartSizing::init(float) {
	}
	
	float SmartSizing::find_size(float parent_size, float target_size) {
		return parent_size * parent_coefficient_ + target_size * target_coefficient_ + addition_;
	}
	
	SmartSizing* SmartSizing::copy() {
		return new SmartSizing{*this};
	}
	
	float SmartSizing::get_parent_size(float object_size) {
		return (object_size - addition_) / parent_coefficient_;
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<SmartSizing>::decode_pointer(const YAML::Node& node, SmartSizing*& smart_sizing) {
		smart_sizing = new SmartSizing{
			conv_def(node["target-coefficient"], 1.f),
			conv_def(node["parent-coefficient"], 0.f),
			conv_def(node["addition"], 0.f)
		};
		return true;

	}
	*/
}