#pragma once

#include "../box.hpp"
#include "../../../../../drawable/iDrawable/iDrawable.hpp"

namespace ui {
	class IBoxWithView : public Box, public IDrawable {
	protected:
		sf::RenderTarget* renderTarget;
		DrawManager drawManager;
		sf::View view;
	
	public:
		IBoxWithView(sf::Vector2f minSize);
		
		void init(InitInfo initInfo) override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		IBoxWithView* copy() override;
	};
}