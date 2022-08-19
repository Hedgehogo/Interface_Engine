#pragma once
#include "../../sizing.hpp"

namespace ui {
	class TargetCoefficientSizing : public Sizing {
	protected:
		float coefficient;
		float addition;
		
	public:
		explicit TargetCoefficientSizing(float coefficient = 1, float addition = 0);
		
		void init(float) override;
		
		float findSize(float, float targetSize) override;
		
		TargetCoefficientSizing* copy() override;
		
		static TargetCoefficientSizing* createFromYaml(const YAML::Node &node);
	};
}
