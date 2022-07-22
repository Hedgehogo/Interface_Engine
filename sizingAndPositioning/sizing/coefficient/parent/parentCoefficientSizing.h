#pragma once
#include "../../sizing.h"

namespace ui {
	class ParentCoefficientSizing : public Sizing {
	protected:
		float coefficient;
		float addition;
	
	public:
		explicit ParentCoefficientSizing(float coefficient = 1, float addition = 0);
		
		void init(float) override;
		
		float findSize(float parentSize, float) override;
		
		float getParentSize(float objectSize) override;
		
		ParentCoefficientSizing* copy() override;
	};
}
