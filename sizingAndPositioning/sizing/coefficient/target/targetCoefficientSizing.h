#pragma once
#include "../../sizing.h"

namespace ui {
	class TargetCoefficientSizing : public Sizing {
	protected:
		float coefficient;
		float addition;
		
	public:
		explicit TargetCoefficientSizing(float coefficient = 1, float addition = 0);
		
		void init(float) override;
		
		float findSize(float, float targetSize) override;
		
		TargetCoefficientSizing* copy() override;
	};
}
