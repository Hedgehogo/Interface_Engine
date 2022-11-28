#pragma once
#include "../iSizing.hpp"
#include <functional>

namespace ui {
	class LambdaSizing : public ISizing {
	public:
		using FindSizeFunc = std::function<float(float parentSize, float targetSize, float normalSize)>;
		using MinSizeFunc = std::function<float(float objectMinSize)>;
		
	protected:
		float normalSize;
		FindSizeFunc findSizeFunc;
		MinSizeFunc minSizeFunc;
		
		void copy(LambdaSizing* lambdaSizing);
		
	public:
		explicit LambdaSizing(FindSizeFunc findSizeFunc, MinSizeFunc minSizeFunc);
		
		void init(float normalSize) override;
		
		float findSize(float parentSize, float targetSize) override;
		
		float getParentSize(float objectMinSize) override;
		
		LambdaSizing* copy() override;
	};
}
