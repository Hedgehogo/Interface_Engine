#pragma once

#include "../IPositioning.hpp"

namespace ie {
	class FnPositioning : public virtual IPositioning {
	public:
		using FindPositionFn = std::function<float(float parent_position, float object_size, float parent_size, float target_size)>;
		
		FnPositioning(FindPositionFn find_position_fn);
		
		float find_position(float parent_position, float object_size, float parent_size, float target_size) override;
		
		FnPositioning* copy() override;
	
	protected:
		FindPositionFn find_position_fn_;
	};
}
