#pragma once

#include "../ISizing.hpp"

namespace ie {
	class ParentCoefficientSizing : public ISizing {
	public:
		struct Make : public ISizing::Make {
			float coefficient = 1;
			float addition = 0;
			
			Make(float coefficient = 1, float addition = 0);
			
			ParentCoefficientSizing* make(float normalSize) override;
		};
		
		ParentCoefficientSizing(Make&& make, float normalSize);
		
		explicit ParentCoefficientSizing(float coefficient = 1, float addition = 0);
		
		void init(float) override;
		
		float findSize(float parentSize, float) override;
		
		float getParentSize(float objectSize) override;
		
		ParentCoefficientSizing* copy() override;
	
	protected:
		float coefficient;
		float addition;
	};
	
	template<>
	struct DecodePointer<ParentCoefficientSizing> {
		static bool decodePointer(const YAML::Node& node, ParentCoefficientSizing*& parentCoefficientSizing);
	};
}
