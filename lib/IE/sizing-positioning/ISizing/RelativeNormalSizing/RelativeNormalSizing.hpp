#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../ISizing.hpp"

namespace ie {
	class RelativeNormalSizing : public virtual ISizing {
	public:
		struct Make : public virtual ISizing::Make {
			auto make(float normal_size) -> RelativeNormalSizing* override;
		};
		
		RelativeNormalSizing(Make&& make, float normal_size);
		
		RelativeNormalSizing();
		
		auto find_size(float, float) -> float override;
		
	protected:
		float normal_size_;
	};
}

template<>
struct ieml::Decode<char, ie::RelativeNormalSizing::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::RelativeNormalSizing::Make>;
};
