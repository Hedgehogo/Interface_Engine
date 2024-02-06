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
	
	float TargetCoefficientSizing::find_size(float, float target_size) {
		return target_size * coefficient_ + addition_;
	}
}

orl::Option<ie::TargetCoefficientSizing::Make> ieml::Decode<char, ie::TargetCoefficientSizing::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::TargetCoefficientSizing::Make{
		map.at("coefficient").except().as<float>().except(),
		map.get_as<float>("addition").ok_or(0.),
	};
}
