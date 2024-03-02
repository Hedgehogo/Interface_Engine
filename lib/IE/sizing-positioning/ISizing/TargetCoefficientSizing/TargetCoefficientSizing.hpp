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
			
			auto make(float normal_size) -> TargetCoefficientSizing* override;
		};
		
		TargetCoefficientSizing(Make&& make, float normal_size);
		
		explicit TargetCoefficientSizing(float coefficient = 1, float addition = 0);
		
		auto find_size(float, float target_size) -> float override;
		
	protected:
		float coefficient_;
		float addition_;
	};
}

template<>
struct ieml::Decode<char, ie::TargetCoefficientSizing::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::TargetCoefficientSizing::Make>;
};
