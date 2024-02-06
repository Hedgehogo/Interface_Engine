#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../ISizing.hpp"

namespace ie {
	class TargetCoefficientSizing : public virtual ISizing {
	public:
		struct Make : public virtual ISizing::Make {
			float coefficient = 1;
			float addition = 0;
			
			Make(float coefficient = 1, float addition = 0);
			
			TargetCoefficientSizing* make(float normal_size) override;
		};
		
		TargetCoefficientSizing(Make&& make, float normal_size);
		
		explicit TargetCoefficientSizing(float coefficient = 1, float addition = 0);
		
		float find_size(float, float target_size) override;
		
	protected:
		float coefficient_;
		float addition_;
	};
}

template<>
struct ieml::Decode<char, ie::TargetCoefficientSizing::Make> {
	static orl::Option<ie::TargetCoefficientSizing::Make> decode(ieml::Node const& node);
};
