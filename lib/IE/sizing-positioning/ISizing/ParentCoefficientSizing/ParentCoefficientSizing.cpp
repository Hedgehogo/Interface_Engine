#include "ParentCoefficientSizing.hpp"

namespace ie {
	ParentCoefficientSizing::Make::Make(float coefficient, float addition) :
		coefficient(coefficient), addition(addition) {
	}
	
	ParentCoefficientSizing* ParentCoefficientSizing::Make::make(float normal_size) {
		return new ParentCoefficientSizing{std::move(*this), normal_size};
	}
	
	ParentCoefficientSizing::ParentCoefficientSizing(Make&& make, float) :
		coefficient_(make.coefficient), addition_(make.addition) {
	}
	
	ParentCoefficientSizing::ParentCoefficientSizing(float coefficient, float addition) : coefficient_(coefficient), addition_(addition) {
	}
	
	float ParentCoefficientSizing::find_size(float parent_size, float) {
		return parent_size * coefficient_ + addition_;
	}
	
	float ParentCoefficientSizing::get_parent_size(float object_size) {
		return (object_size - addition_) / coefficient_;
	}
}

orl::Option<ie::ParentCoefficientSizing::Make> ieml::Decode<char, ie::ParentCoefficientSizing::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::ParentCoefficientSizing::Make{
		map.at("coefficient").except().as<float>().except(),
		map.get_as<float>("addition").except().ok_or(0.)
	};
}
