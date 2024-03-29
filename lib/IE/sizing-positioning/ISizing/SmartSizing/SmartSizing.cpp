#include "SmartSizing.hpp"

namespace ie {
	SmartSizing::Make::Make(float target_coefficient, float parent_coefficient, float addition) :
		target_coefficient(target_coefficient), parent_coefficient(parent_coefficient), addition(addition) {
	}
	
	auto SmartSizing::Make::make(float normal_size) -> SmartSizing* {
		return new SmartSizing{std::move(*this), normal_size};
	}
	
	SmartSizing::SmartSizing(Make&& make, float) :
		target_coefficient_(make.target_coefficient), parent_coefficient_(make.parent_coefficient), addition_(make.addition) {
	}
	
	SmartSizing::SmartSizing(float target_coefficient, float parent_coefficient, float addition) :
		target_coefficient_(target_coefficient), parent_coefficient_(parent_coefficient), addition_(addition) {
	}
	
	auto SmartSizing::find_size(float parent_size, float target_size) -> float {
		return parent_size * parent_coefficient_ + target_size * target_coefficient_ + addition_;
	}
	
	auto SmartSizing::get_parent_size(float object_size) -> float {
		return (object_size - addition_) / parent_coefficient_;
	}
}

auto ieml::Decode<char, ie::SmartSizing::Make>::decode(ieml::Node const& node) -> orl::Option<ie::SmartSizing::Make> {
	auto map{node.get_map_view().except()};
	return ie::SmartSizing::Make{
		map.get_as<float>("target-coefficient").except().ok_or(1.),
		map.get_as<float>("parent-coefficient").except().ok_or(0.),
		map.get_as<float>("addition").except().ok_or(0.),
	};
}
