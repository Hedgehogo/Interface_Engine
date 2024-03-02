#include "TargetCoefficientSizing.hpp"

namespace ie {
	TargetCoefficientSizing::Make::Make(float coefficient, float addition) :
		coefficient(coefficient), addition(addition) {
	}
	
	auto TargetCoefficientSizing::Make::make(float normal_size) -> TargetCoefficientSizing* {
		return new TargetCoefficientSizing{std::move(*this), normal_size};
	}
	
	TargetCoefficientSizing::TargetCoefficientSizing(Make&& make, float) :
		coefficient_(make.coefficient), addition_(make.addition) {
	}
	
	TargetCoefficientSizing::TargetCoefficientSizing(float coefficient, float addition) : coefficient_(coefficient), addition_(addition) {
	}
	
	auto TargetCoefficientSizing::find_size(float, float target_size) -> float {
		return target_size * coefficient_ + addition_;
	}
}

auto ieml::Decode<char, ie::TargetCoefficientSizing::Make>::decode(ieml::Node const& node) -> orl::Option<ie::TargetCoefficientSizing::Make> {
	auto map{node.get_map_view().except()};
	return ie::TargetCoefficientSizing::Make{
		map.at("coefficient").except().as<float>().except(),
		map.get_as<float>("addition").except().ok_or(0.),
	};
}
