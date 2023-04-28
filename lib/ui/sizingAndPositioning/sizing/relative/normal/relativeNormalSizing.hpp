#pragma once
#include "../../iSizing.hpp"

namespace ui {
	class RelativeNormalSizing : public ISizing {
	protected:
		float normalSize;
		
		void copy(RelativeNormalSizing* relativeNormalSizing);
		
	public:
		RelativeNormalSizing();
		
		void init(float normalSize) override;
		
		float findSize(float,float) override;
		
		RelativeNormalSizing* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, RelativeNormalSizing *&relativeNormalSizing);
	
	template<>
	struct DecodePointer<RelativeNormalSizing> {
		static bool decodePointer(const YAML::Node &node, RelativeNormalSizing *&relativeNormalSizing);
	};
}
