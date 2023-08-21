#pragma once

#include "../ISizing.hpp"

namespace ui {
	class TargetCoefficientSizing : public ISizing {
	public:
		struct Make : public ISizing::Make {
			float coefficient = 1;
			float addition = 0;
			
			Make(float coefficient = 1, float addition = 0);
			
			TargetCoefficientSizing* make(float normalSize) override;
		};
		
		TargetCoefficientSizing(Make&& make, float normalSize);
		
		explicit TargetCoefficientSizing(float coefficient = 1, float addition = 0);
		
		void init(float) override;
		
		float findSize(float, float targetSize) override;
		
		TargetCoefficientSizing* copy() override;
	
	protected:
		float coefficient;
		float addition;
	};
	
	template<>
	struct DecodePointer<TargetCoefficientSizing> {
		static bool decodePointer(const YAML::Node& node, TargetCoefficientSizing*& targetCoefficientSizing);
	};
}
