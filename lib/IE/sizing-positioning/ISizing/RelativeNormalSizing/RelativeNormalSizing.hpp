#pragma once

#include "../ISizing.hpp"

namespace ie {
	class RelativeNormalSizing : public virtual ISizing {
	public:
		struct Make : public virtual ISizing::Make {
			RelativeNormalSizing* make(float normal_size) override;
		};
		
		RelativeNormalSizing(Make&& make, float normal_size);
		
		RelativeNormalSizing();
		
		void init(float normal_size) override;
		
		float find_size(float, float) override;
		
		RelativeNormalSizing* copy() override;
	
	protected:
		float normal_size;
	};
	
	template<>
	struct DecodePointer<RelativeNormalSizing> {
		static bool decode_pointer(const YAML::Node&, RelativeNormalSizing*& relative_normal_sizing);
	};
}
