#pragma once
#include "../../sizing.hpp"

namespace ui {
	class RelativeParentSizing : public Sizing {
	protected:
		float addition;
		
	public:
		explicit RelativeParentSizing(float addition = 0);
		
		void init(float) override;
		
		float findSize(float parentSize, float) override;
		
		float getParentSize(float objectSize) override;
		
		RelativeParentSizing* copy() override;
		
		static RelativeParentSizing* createFromYaml(const YAML::Node &node);
	};
}
