#pragma once
#include "../../iSizing.hpp"

namespace ui {
	class TargetCoefficientSizing : public ISizing {
	protected:
		float coefficient;
		float addition;
		
	public:
		explicit TargetCoefficientSizing(float coefficient = 1, float addition = 0);
		
		void init(float) override;
		
		float findSize(float, float targetSize) override;
		
		TargetCoefficientSizing* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, TargetCoefficientSizing *&targetCoefficientSizing);
}
