#pragma once

#include "../IPositioning.hpp"

namespace ie {
	class FnPositioning : public virtual IPositioning {
	public:
		using FindPositionFn = std::function<float(float parentPosition, float objectSize, float parentSize, float targetSize)>;
		
		FnPositioning(FindPositionFn findPositionFn);
		
		float findPosition(float parentPosition, float objectSize, float parentSize, float targetSize) override;
		
		FnPositioning* copy() override;
	
	protected:
		FindPositionFn findPositionFn;
	};
}
