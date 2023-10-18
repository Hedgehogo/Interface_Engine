#pragma once

#include "../ISizing.hpp"

namespace ie {
	class TargetCoefficientSizing : public virtual ISizing {
	public:
		struct Make : public virtual ISizing::Make {
			float coefficient = 1;
			float addition = 0;
			
			Make(float coefficient = 1, float addition = 0);
			
			TargetCoefficientSizing* make(float normal_size) override;
		};
		
		TargetCoefficientSizing(Make&& make, float normal_size);
		
		explicit TargetCoefficientSizing(float coefficient = 1, float addition = 0);
		
		void init(float) override;
		
		float find_size(float, float target_size) override;
		
		TargetCoefficientSizing* copy() override;
	
	protected:
		float coefficient;
		float addition;
	};
	
	template<>
	struct DecodePointer<TargetCoefficientSizing> {
		static bool decode_pointer(const YAML::Node& node, TargetCoefficientSizing*& target_coefficient_sizing);
	};
}
