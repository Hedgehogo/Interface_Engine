#pragma once

#include "../IUninteractive.hpp"

namespace ui {
	class OnlyDrawable : public IUninteractive, public IDrawable {
	public:
		OnlyDrawable(InitInfo initInfo);
		
		OnlyDrawable();
		
		sf::RenderTarget& getRenderTarget();
		
		void init(InitInfo initInfo) override;
	
	protected:
		sf::RenderTarget* renderTarget;
	};
}