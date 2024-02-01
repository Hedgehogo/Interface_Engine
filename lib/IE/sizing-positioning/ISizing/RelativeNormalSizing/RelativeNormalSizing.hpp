#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../ISizing.hpp"

namespace ie {
	class RelativeNormalSizing : public virtual ISizing {
	public:
		struct Make : public virtual ISizing::Make {
			RelativeNormalSizing* make(float normal_size) override;
		};
		
		RelativeNormalSizing(Make&& make, float normal_size);
		
		RelativeNormalSizing();
		
		float find_size(float, float) override;
		
	protected:
		float normal_size_;
	};
}

template<>
struct ieml::Decode<char, ie::RelativeNormalSizing::Make> {
	static orl::Option<ie::RelativeNormalSizing::Make> decode(ieml::Node const& node);
};
