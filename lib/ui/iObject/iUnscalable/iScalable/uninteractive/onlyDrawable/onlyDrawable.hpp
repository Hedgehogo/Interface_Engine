#pragma once

#include "../uninteractive.hpp"

namespace ui {
	class OnlyDrawable : public IUninteractive, public IDrawable {
	public:
		OnlyDrawable(InitInfo initInfo);
		
		OnlyDrawable();
		
		void init(InitInfo initInfo) override;
	
	protected:
		sf::RenderTarget* renderTarget;
	};
}