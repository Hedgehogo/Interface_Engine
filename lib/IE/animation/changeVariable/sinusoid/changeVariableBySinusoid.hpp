#pragma once

#include "../iChangeVariable.hpp"

namespace ui {
	class ChangeVariableBySinusoid : public IChangeVariable {
	public:
		ChangeVariableBySinusoid(float size, float a = 0, float b = 1, float= 1, float d = 0);
		
		float getSize() override;
		
		float operator()(float frame) override;
		
		IChangeVariable* copy() override;
	
	protected:
		const float a, b, c, d, size;
	};
	
	template<>
	struct DecodePointer<ChangeVariableBySinusoid> {
		static bool decodePointer(const YAML::Node& node, ChangeVariableBySinusoid*& changeVariableBySinusoid);
	};
}