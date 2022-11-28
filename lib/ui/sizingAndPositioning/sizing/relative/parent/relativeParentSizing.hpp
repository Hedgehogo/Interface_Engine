#pragma once
#include "../../iSizing.hpp"

namespace ui {
	class RelativeParentSizing : public ISizing {
	protected:
		float addition;
		
	public:
		explicit RelativeParentSizing(float addition = 0);
		
		void init(float) override;
		
		float findSize(float parentSize, float) override;
		
		float getParentSize(float objectSize) override;
		
		RelativeParentSizing* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, RelativeParentSizing *&relativeParentSizing);
}
