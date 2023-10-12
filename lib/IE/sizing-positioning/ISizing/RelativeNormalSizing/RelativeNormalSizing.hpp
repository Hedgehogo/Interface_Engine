#pragma once

#include "../ISizing.hpp"

namespace ie {
	class RelativeNormalSizing : public virtual ISizing {
	public:
		struct Make : public virtual ISizing::Make {
			RelativeNormalSizing* make(float normalSize) override;
		};
		
		RelativeNormalSizing(Make&& make, float normalSize);
		
		RelativeNormalSizing();
		
		void init(float normalSize) override;
		
		float findSize(float, float) override;
		
		RelativeNormalSizing* copy() override;
	
	protected:
		float normalSize;
	};
	
	template<>
	struct DecodePointer<RelativeNormalSizing> {
		static bool decodePointer(const YAML::Node&, RelativeNormalSizing*& relativeNormalSizing);
	};
}
