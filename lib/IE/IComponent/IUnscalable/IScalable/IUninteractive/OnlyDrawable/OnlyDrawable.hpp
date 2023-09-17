#pragma once

#include "../IUninteractive.hpp"

namespace ie {
	class OnlyDrawable : public virtual IUninteractive, public virtual IDrawable {
	public:
		OnlyDrawable(InitInfo initInfo);
		
		OnlyDrawable();
		
		sf::RenderTarget& getRenderTarget();
		
		void init(InitInfo initInfo) override;
	
	protected:
		sf::RenderTarget* renderTarget;
	};
}