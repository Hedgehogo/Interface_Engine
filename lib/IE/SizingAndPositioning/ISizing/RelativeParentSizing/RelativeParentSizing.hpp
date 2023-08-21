#pragma once

#include "../ISizing.hpp"

namespace ui {
	class RelativeParentSizing : public ISizing {
	public:
		struct Make : public ISizing::Make {
			float addition = 0;
			
			Make(float addition = 0);
			
			RelativeParentSizing* make(float normalSize) override;
		};
		
		RelativeParentSizing(Make&& make, float normalSize);
		
		explicit RelativeParentSizing(float addition = 0);
		
		void init(float) override;
		
		float findSize(float parentSize, float) override;
		
		float getParentSize(float objectSize) override;
		
		RelativeParentSizing* copy() override;
	
	protected:
		float addition;
	};
	
	template<>
	struct DecodePointer<RelativeParentSizing> {
		static bool decodePointer(const YAML::Node& node, RelativeParentSizing*& relativeParentSizing);
	};
}
