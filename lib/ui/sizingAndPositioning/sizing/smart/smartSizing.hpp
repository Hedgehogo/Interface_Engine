#pragma once
#include "../sizing.hpp"

namespace ui {
	class SmartSizing : public Sizing {
	protected:
		float targetCoefficient;
		float parentCoefficient;
		float addition;
	
	public:
		explicit SmartSizing(float targetCoefficient = 1, float parentCoefficient = 0, float addition = 0);
		
		void init(float) override;
		
		float findSize(float parentSize, float targetSize) override;
		
		float getParentSize(float objectSize) override;
		
		SmartSizing* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, SmartSizing *&smartSizing);
	
	Sizing* createSizing(float targetCoefficient, float parentCoefficient, float addition);
}
