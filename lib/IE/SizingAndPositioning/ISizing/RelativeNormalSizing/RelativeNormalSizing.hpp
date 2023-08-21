#pragma once

#include "../ISizing.hpp"

namespace ui {
	class RelativeNormalSizing : public ISizing {
	public:
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
