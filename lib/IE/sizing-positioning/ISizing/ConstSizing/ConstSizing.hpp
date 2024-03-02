#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../ISizing.hpp"

namespace ie {
	class ConstSizing : public virtual ISizing {
	public:
		struct Make : public virtual ISizing::Make {
			float size;
			
			Make(float size);
			
			auto make(float normal_size) -> ConstSizing* override;
		};
		
		ConstSizing(Make&& make, float normal_size);
		
		ConstSizing(float size);
		
		auto find_size(float, float) -> float override;
		
	protected:
		float size_;
	};
}

template<>
struct ieml::Decode<char, ie::ConstSizing::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::ConstSizing::Make>;
};
