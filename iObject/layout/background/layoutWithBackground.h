#pragma once
#include "../layout.h"
#include "../../iUnscalable/iScalable/iDrawable/iDrawable.h"

namespace ui {
	class LayoutWithBackground : public virtual Layout {
	protected:
		IDrawable* background;
		
	public:
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		explicit LayoutWithBackground(IDrawable* background);
		
		~LayoutWithBackground() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
