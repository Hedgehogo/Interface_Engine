#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../ISizing.hpp"

namespace ie {
	class ConstSizing : public virtual ISizing {
	public:
		struct Make : public virtual ISizing::Make {
			float size;
			
			Make(float size);
			
			ConstSizing* make(float normal_size) override;
		};
		
		ConstSizing(Make&& make, float normal_size);
		
		ConstSizing(float size);
		
		void init(float) override;
		
		float find_size(float, float) override;
		
		ConstSizing* copy() override;
	
	protected:
		float size_;
	};
}

template<>
struct ieml::Decode<char, ie::ConstSizing::Make> {
	static orl::Option<ie::ConstSizing::Make> decode(ieml::Node const& node);
};
