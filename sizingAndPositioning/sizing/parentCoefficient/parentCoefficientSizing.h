#pragma once
#include "../sizing.h"

namespace ui {
	class ParentCoefficientSizing : public Sizing {
	protected:
		float coefficient;
		float addition;
	
	public:
		explicit ParentCoefficientSizing(float coefficient, float addition = 0);
		
		void init(sf::RenderTarget &, float) override;
		
		float findSize(float parentSize) override;
		
		ParentCoefficientSizing* copy() override;
	};
	
	Sizing* createSize(float coefficient, float addition);
}
