#pragma once
#include "../sizing.h"

namespace ui {
	class ConstSizing : public Sizing {
	protected:
		float size;
		
	public:
		ConstSizing(float size);
		
		void init(sf::RenderTarget&, float) override;
		
		float findSize(float) override;
		
		ConstSizing* copy() override;
	};
	
	Sizing* createSize(float constSize);
}
