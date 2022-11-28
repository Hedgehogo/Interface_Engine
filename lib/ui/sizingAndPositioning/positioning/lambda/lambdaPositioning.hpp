#pragma once
#include "../iPositioning.hpp"

namespace ui {
	class LambdaPositioning : public IPositioning {
	public:
		using FindPositionFunc = std::function<float(float parentPosition, float objectSize, float parentSize, float targetSize)>;
	
	protected:
		FindPositionFunc findPositionFunc;
		
	public:
		explicit LambdaPositioning(FindPositionFunc findPositionFunc);
		
		float findPosition(float parentPosition, float objectSize, float parentSize, float targetSize) override;
		
		LambdaPositioning* copy() override;
	};
}
