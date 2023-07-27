#pragma once

#include "../../iSizing.hpp"

namespace ui {
	class ParentCoefficientSizing : public ISizing {
	public:
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
