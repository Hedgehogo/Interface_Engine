#pragma once

#include "../ISizing.hpp"
#include <functional>

namespace ie {
	class LambdaSizing : public virtual ISizing {
	public:
		using FindSizeFunc = std::function<float(float parentSize, float targetSize, float normalSize)>;
		using MinSizeFunc = std::function<float(float objectMinSize)>;
		
		struct Make : public virtual ISizing::Make {
			FindSizeFunc findSizeFunc;
			MinSizeFunc minSizeFunc;
			
			Make(FindSizeFunc findSizeFunc, MinSizeFunc minSizeFunc);
			
			LambdaSizing* make(float normalSize) override;
		};
		
		LambdaSizing(Make&& make, float normalSize);
		
		explicit LambdaSizing(FindSizeFunc findSizeFunc, MinSizeFunc minSizeFunc);
		
		void init(float normalSize) override;
		
		float findSize(float parentSize, float targetSize) override;
		
		float getParentSize(float objectMinSize) override;
		
		LambdaSizing* copy() override;
	
	protected:
		FindSizeFunc findSizeFunc;
		MinSizeFunc minSizeFunc;
		float normalSize;
	};
}
