#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../ISizing.hpp"

namespace ie {
	class ParentCoefficientSizing : public virtual ISizing {
	public:
		struct Make : public virtual ISizing::Make {
			float coefficient = 1;
			float addition = 0;
			
			Make(float coefficient = 1, float addition = 0);
			
			auto make(float normal_size) -> ParentCoefficientSizing* override;
		};
		
		ParentCoefficientSizing(Make&& make, float normal_size);
		
		explicit ParentCoefficientSizing(float coefficient = 1, float addition = 0);
		
		auto find_size(float parent_size, float) -> float override;
		
		auto get_parent_size(float object_size) -> float override;
		
	protected:
		float coefficient_;
		float addition_;
	};
}

template<>
struct ieml::Decode<char, ie::ParentCoefficientSizing::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::ParentCoefficientSizing::Make>;
};
