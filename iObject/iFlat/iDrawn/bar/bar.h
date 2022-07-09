#pragma once
#include "../iDrawn.h"
#include "../empty/empty.h"

namespace ui {
	class Bar : public IDrawn, public Layout {
	protected:
		IDrawn* strip;
		IDrawn* background;
		bool horizontal;
		float offset;
		int division;
		float value;
		
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
	public:
		explicit Bar(IDrawn* background, IDrawn* strip, float offset = 0, bool horizontal = true);
		
		explicit Bar(IDrawn *background, IDrawn *strip, int division, float offset = 0, bool horizontal = true);
		
		float getValue();
		
		void setValue(float value);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		Bar* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition) override;
	};
}
