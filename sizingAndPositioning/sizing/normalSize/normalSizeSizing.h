#pragma once
#include "../sizing.h"

namespace ui {
	class NormalSizeSizing : public Sizing {
	protected:
		float size;
		
		void copy(NormalSizeSizing* normalSizeSizing);
		
	public:
		NormalSizeSizing();
		
		void init(sf::RenderTarget &, float normalSize) override;
		
		float findSize(float) override;
		
		NormalSizeSizing* copy() override;
	};
	
	Sizing* createSize();
}