#pragma once

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
	
	template<>
	struct DecodePointer<ConstSizing> {
		static bool decode_pointer(const YAML::Node& node, ConstSizing*& const_sizing);
	};
}
