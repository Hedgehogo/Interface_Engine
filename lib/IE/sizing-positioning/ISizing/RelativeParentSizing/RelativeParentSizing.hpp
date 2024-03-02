#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../ISizing.hpp"

namespace ie {
	class RelativeParentSizing : public virtual ISizing {
	public:
		struct Make : public virtual ISizing::Make {
			float addition = 0;
			
			Make(float addition = 0);
			
			auto make(float normal_size) -> RelativeParentSizing* override;
		};
		
		RelativeParentSizing(Make&& make, float normal_size);
		
		explicit RelativeParentSizing(float addition = 0);
		
		auto find_size(float parent_size, float) -> float override;
		
		auto get_parent_size(float object_size) -> float override;
		
	protected:
		float addition_;
	};
}

template<>
struct ieml::Decode<char, ie::RelativeParentSizing::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::RelativeParentSizing::Make>;
};
