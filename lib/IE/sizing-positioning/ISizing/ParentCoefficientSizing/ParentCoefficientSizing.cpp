#include "ParentCoefficientSizing.hpp"

namespace ie {
	ParentCoefficientSizing::Make::Make(float coefficient, float addition) :
		coefficient(coefficient), addition(addition) {
	}
	
	auto ParentCoefficientSizing::Make::make(float normal_size) -> ParentCoefficientSizing* {
		return new ParentCoefficientSizing{std::move(*this), normal_size};
	}
	
	ParentCoefficientSizing::ParentCoefficientSizing(Make&& make, float) :
		coefficient_(make.coefficient), addition_(make.addition) {
	}
	
	ParentCoefficientSizing::ParentCoefficientSizing(float coefficient, float addition) : coefficient_(coefficient), addition_(addition) {
	}
	
	auto ParentCoefficientSizing::find_size(float parent_size, float) -> float {
		return parent_size * coefficient_ + addition_;
	}
	
	auto ParentCoefficientSizing::get_parent_size(float object_size) -> float {
		return (object_size - addition_) / coefficient_;
	}
}

auto ieml::Decode<char, ie::ParentCoefficientSizing::Make>::decode(ieml::Node const& node) -> orl::Option<ie::ParentCoefficientSizing::Make> {
	auto map{node.get_map_view().except()};
	return ie::ParentCoefficientSizing::Make{
		map.at("coefficient").except().as<float>().except(),
		map.get_as<float>("addition").except().ok_or(0.)
	};
}
