#pragma once
#include "../iSizing.hpp"

namespace ui {
	class ConstSizing : public ISizing {
	protected:
		float size;
		
	public:
		ConstSizing(float size);
		
		void init(float) override;
		
		float findSize(float, float) override;
		
		ConstSizing* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, ConstSizing *&constSizing);
}
