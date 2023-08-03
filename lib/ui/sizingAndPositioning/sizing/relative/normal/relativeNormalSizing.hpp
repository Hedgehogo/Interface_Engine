#pragma once

#include "../../iSizing.hpp"

namespace ui {
	class RelativeNormalSizing : public ISizing {
	protected:
		void copy(RelativeNormalSizing* relativeNormalSizing);
	
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
