#pragma once
#include "../sizing.h"

namespace ui {
	class LambdaSizing : public Sizing {
	protected:
		float normalSize;
		float (*sizing)(float parentSize, float targetSize, float normalSize);
		float (*minSize)(float objectMinSize);
		
		void copy(LambdaSizing* lambdaSizing);
	
	public:
		explicit LambdaSizing(float (*findSize)(float parentSize, float targetSize, float normalSize), float (*getParentMinSize)(float objectMinSize));
		
		void init(float normalSize) override;
		
		float findSize(float parentSize, float targetSize) override;
		
		float getParentSize(float objectSize) override;
		
		LambdaSizing* copy() override;
	};
}
