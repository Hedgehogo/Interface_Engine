#pragma once

#include "../layer.h"
#include "../../onlyDrawable/onlyDrawable.h"
#include "../../../../layout/object/layoutWithObject.h"
#include "../../../../../interaction/interactionStack/interactionStack.h"
#include "../../../../../interaction/interactionManager/interactionManager.h"

namespace ui {
	class LayerWithConstBezel : public Layer, public LayoutWithObject {
	protected:
		OnlyDrawable *bezel;
		float thickness;
		
	public:
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		LayerWithConstBezel(IScalable *object, OnlyDrawable *bezel, float thickness, sf::Vector2f minSize = {0, 0});
		
		~LayerWithConstBezel() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void update() override;
		
		LayerWithConstBezel* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	typedef LayerWithConstBezel LayerWCBezel;
	typedef LayerWithConstBezel LWCBe;
}
