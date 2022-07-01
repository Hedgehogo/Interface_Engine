#pragma once
#include "../sizing.h"

namespace ui {
	class RelativeParentSizing : public Sizing {
	protected:
		float addition;
		
	public:
		RelativeParentSizing(float addition = 0);
		
		void init(sf::RenderTarget &, float) override;
		
		float findSize(float parentSize) override;
		
		RelativeParentSizing* copy() override;
	};
}
