#pragma once
#include "../sizing.h"

namespace ui {
	class RelativeParentSizing : public Sizing {
	protected:
		float addition;
		
	public:
		explicit RelativeParentSizing(float addition = 0);
		
		void init(float) override;
		
		float findSize(float parentSize, float) override;
		
		RelativeParentSizing* copy() override;
	};
}
