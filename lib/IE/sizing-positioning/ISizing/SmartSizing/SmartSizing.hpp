#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../ISizing.hpp"

namespace ie {
	class SmartSizing : public virtual ISizing {
	public:
		struct Make : public virtual ISizing::Make {
			float target_coefficient = 1;
			float parent_coefficient = 0;
			float addition = 0;
			
			Make(float target_coefficient = 1, float parent_coefficient = 0, float addition = 0);
			
			auto make(float normal_size) -> SmartSizing* override;
		};
		
		SmartSizing(Make&& make, float normal_size);
		
		explicit SmartSizing(float target_coefficient = 1, float parent_coefficient = 0, float addition = 0);
		
		auto find_size(float parent_size, float target_size) -> float override;
		
		auto get_parent_size(float object_size) -> float override;
	
	protected:
		float target_coefficient_;
		float parent_coefficient_;
		float addition_;
	};
}

template<>
struct ieml::Decode<char, ie::SmartSizing::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::SmartSizing::Make>;
};
