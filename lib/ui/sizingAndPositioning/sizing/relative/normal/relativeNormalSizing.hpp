#pragma once
#include "../../sizing.hpp"

namespace ui {
	class RelativeNormalSizing : public Sizing {
	protected:
		float normalSize;
		
		void copy(RelativeNormalSizing* relativeNormalSizing);
		
	public:
		RelativeNormalSizing();
		
		void init(float normalSize) override;
		
		float findSize(float,float) override;
		
		RelativeNormalSizing* copy() override;
		
		static RelativeNormalSizing* createFromYaml(const YAML::Node &);
	};
	
	Sizing* createSize();
}
