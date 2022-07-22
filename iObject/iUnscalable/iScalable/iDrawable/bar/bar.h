#pragma once
#include "../iDrawable.h"
#include "../empty/empty.h"
#include "../../../../layout/background/layoutWithBackground.h"

namespace ui {
	class Bar : public IDrawable, public LayoutWithBackground {
	protected:
		IDrawable* strip;
		bool horizontal;
		float offset;
		int division;
		float value;
		
		void copy(Bar* bar);
		
	public:
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		explicit Bar(IDrawable* background, IDrawable* strip, float offset = 0, bool horizontal = true);
		
		explicit Bar(IDrawable *background, IDrawable *strip, int division, float offset = 0, bool horizontal = true);
		
		~Bar() override;
		
		float getValue();
		
		void setValue(float value);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		Bar* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
