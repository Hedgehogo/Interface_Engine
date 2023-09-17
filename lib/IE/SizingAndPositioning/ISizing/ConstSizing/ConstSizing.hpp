#pragma once

#include "../ISizing.hpp"

namespace ie {
	class ConstSizing : public virtual ISizing {
	public:
		struct Make : public virtual ISizing::Make {
			float size;
			
			Make(float size);
			
			ConstSizing* make(float normalSize) override;
		};
		
		ConstSizing(Make&& make, float normalSize);
		
		ConstSizing(float size);
		
		void init(float) override;
		
		float findSize(float, float) override;
		
		ConstSizing* copy() override;
	
	protected:
		float size;
	};
	
	template<>
	struct DecodePointer<ConstSizing> {
		static bool decodePointer(const YAML::Node& node, ConstSizing*& constSizing);
	};
}
