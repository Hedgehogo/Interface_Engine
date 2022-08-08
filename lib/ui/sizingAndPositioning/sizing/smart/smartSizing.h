#pragma once
#include "../sizing.h"

namespace ui {
	class SmartSizing : public Sizing {
	protected:
		float targetCoefficient;
		float parentCoefficient;
		float addition;
	
	public:
		explicit SmartSizing(float parentCoefficient = 1, float targetCoefficient = 0, float addition = 0);
		
		void init(float) override;
		
		float findSize(float parentSize, float targetSize) override;
		
		float getParentSize(float objectSize) override;
		
		SmartSizing* copy() override;
	};
	
	Sizing* createSizing(float targetCoefficient, float parentCoefficient, float addition);
}
