#pragma once
#include "../sizing.h"

namespace ui {
	class ConstSizing : public Sizing {
	protected:
		float size;
		
	public:
		ConstSizing(float size);
		
		void init(float) override;
		
		float findSize(float, float) override;
		
		ConstSizing* copy() override;
	};
	
	Sizing* createSize(float constSize);
}
