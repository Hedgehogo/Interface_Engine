#pragma once

#include "../uninteractive.hpp"

namespace ui {
	class OnlyDrawable : public IUninteractive, public IDrawable {
	public:
		OnlyDrawable();
		
		void init(InitInfo initInfo) override;
	
	protected:
		sf::RenderTarget* renderTarget;
	};
}