#pragma once
#include "../../sizing.hpp"

namespace ui {
	class RelativeNormalSizing : public Sizing {
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
	
	Sizing* createSize();
}
