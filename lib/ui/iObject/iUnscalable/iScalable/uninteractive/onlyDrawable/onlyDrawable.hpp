#pragma once

#include "../uninteractive.hpp"

namespace ui {
	class OnlyDrawable : public IUninteractive, public IDrawable {
	protected:
		sf::RenderTarget* renderTarget;
		
		void copy(OnlyDrawable* OnlyDrawable);
	
	public:
		OnlyDrawable();
		
		void init(InitInfo initInfo) override;
	};
}