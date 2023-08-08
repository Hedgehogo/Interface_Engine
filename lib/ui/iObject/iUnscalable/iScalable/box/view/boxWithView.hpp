#pragma once

#include "../box.hpp"
#include "../../../../../drawable/iDrawable/iDrawable.hpp"

namespace ui {
	class BoxWithView : public Box, public IDrawable {
	public:
		BoxWithView(sf::Vector2f minSize, InitInfo initInfo);
		
		BoxWithView(sf::Vector2f minSize);
		
		BoxWithView(const BoxWithView& other);
		
		void init(InitInfo initInfo) override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		BoxWithView* copy() override = 0;
	
	protected:
		DrawManager drawManager;
		sf::RenderTarget* renderTarget;
		sf::View view;
	};
}