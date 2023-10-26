#pragma once

#include "../IChangeVariable.hpp"

namespace ie {
	class ChangeVariableBySinusoid : public virtual IChangeVariable {
	public:
		ChangeVariableBySinusoid(float size, float a = 0, float b = 1, float= 1, float d = 0);
		
		float get_size() override;
		
		float operator()(float frame) override;
		
		IChangeVariable* copy() override;
	
	protected:
		const float a_, b_, c_, d_, size_;
	};
	
	template<>
	struct DecodePointer<ChangeVariableBySinusoid> {
		static bool decode_pointer(const YAML::Node& node, ChangeVariableBySinusoid*& change_variable_by_sinusoid);
	};
}