#pragma once
#include "../sizing.h"

namespace ui {
	class LambdaSizing : public Sizing {
	protected:
		float normalSize;
		float (*sizing)(float parentSize, float targetSize, float normalSize);
		
		void copy(LambdaSizing* lambdaSizing);
	
	public:
		explicit LambdaSizing(float (*findSize)(float parentSize, float targetSize, float normalSize));
		
		void init(float normalSize) override;
		
		float findSize(float parentSize, float targetSize) override;
		
		LambdaSizing* copy() override;
	};
}
