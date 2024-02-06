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
			
			ParentCoefficientSizing* make(float normal_size) override;
		};
		
		ParentCoefficientSizing(Make&& make, float normal_size);
		
		explicit ParentCoefficientSizing(float coefficient = 1, float addition = 0);
		
		float find_size(float parent_size, float) override;
		
		float get_parent_size(float object_size) override;
		
	protected:
		float coefficient_;
		float addition_;
	};
}

template<>
struct ieml::Decode<char, ie::ParentCoefficientSizing::Make> {
	static orl::Option<ie::ParentCoefficientSizing::Make> decode(ieml::Node const& node);
};
