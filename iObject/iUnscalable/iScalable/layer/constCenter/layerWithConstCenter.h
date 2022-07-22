#pragma once

#include "../layer.h"
#include "../../onlyDrawable/onlyDrawable.h"
#include "../../../../layout/object/layoutWithObject.h"
#include "../../../../layout/background/layoutWithBackground.h"

namespace ui {
	class LayerWithConstCenter : public Layer, public LayoutWithObject, public LayoutWithBackground {
	protected:
		float aspectRatio;
	
	public:
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		LayerWithConstCenter(IScalable *object, OnlyDrawable *background, float aspectRatio, sf::Vector2f minSize = sf::Vector2f());
		
		void setAspectRatio(float aspectRatio);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		LayerWithConstCenter* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	typedef LayerWithConstCenter LayerWCCenter;
	typedef LayerWithConstCenter LWCC;
}
