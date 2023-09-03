#pragma once

#include "../IPositioning.hpp"

namespace ie {
	class LambdaPositioning : public virtual IPositioning {
	public:
		using FindPositionFunc = std::function<float(float parentPosition, float objectSize, float parentSize, float targetSize)>;
	
		explicit LambdaPositioning(FindPositionFunc findPositionFunc);
		
		float findPosition(float parentPosition, float objectSize, float parentSize, float targetSize) override;
		
		LambdaPositioning* copy() override;
	
	protected:
		FindPositionFunc findPositionFunc;
	};
}
