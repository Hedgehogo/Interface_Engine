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
}

orl::Option<ie::SmartSizing::Make> ieml::Decode<char, ie::SmartSizing::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::SmartSizing::Make{
		map.get_as<float>("target-coefficient").ok_or(1.),
		map.get_as<float>("parent-coefficient").ok_or(0.),
		map.get_as<float>("addition").ok_or(0.),
	};
}
