#pragma once
#include "../sizing.hpp"

namespace ui {
	class ConstSizing : public Sizing {
	protected:
		float size;
		
	public:
		ConstSizing(float size);
		
		void init(float) override;
		
		float findSize(float, float) override;
		
		ConstSizing* copy() override;
		
		static ConstSizing* createFromYaml(const YAML::Node &node);
	};
	
	Sizing* createSize(float constSize);
}
