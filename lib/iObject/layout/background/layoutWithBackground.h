#pragma once
#include "../layout.h"
#include "../../iUnscalable/iScalable/onlyDrawable/onlyDrawable.h"

namespace ui {
	class LayoutWithBackground : public virtual Layout {
	protected:
		OnlyDrawable* background;
		
	public:
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		explicit LayoutWithBackground(OnlyDrawable* background);
		
		~LayoutWithBackground() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
