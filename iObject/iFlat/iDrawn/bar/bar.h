#pragma once
#include "../iDrawn.h"
#include "../empty/empty.h"

namespace ui {
	class Bar : public IDrawn {
	protected:
		IDrawn* strip;
		IDrawn* background;
		sf::Vector2f position;
		sf::Vector2f size;
		bool horizontal;
		float offset;
		int division;
		float value;
		
		void init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelStack &overlayStack) override;
		
	public:
		explicit Bar(IDrawn* background, IDrawn* strip, float offset = 0, bool horizontal = true);
		
		explicit Bar(IDrawn *background, IDrawn *strip, int division, float offset = 0, bool horizontal = true);
		
		float getValue();
		
		void setValue(float value);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
	};
}
