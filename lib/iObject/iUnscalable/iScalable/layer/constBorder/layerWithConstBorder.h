#pragma once
#include <SFML/Graphics.hpp>
#include "../layer.h"
#include "../../iScalable.h"
#include "../../../../layout/twoObjects/layoutWithTwoObjects.h"
#include "../../../../../interaction/interactionStack/interactionStack.h"

namespace ui {
	class LayerWithConstBorder : public Layer, public LayoutWithTwoObjects {
	protected:
		float borderDistance;
		Side side;
	
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;
		
		LayerWithConstBorder(IScalable *constObject, IScalable *secondObject, Side side, float borderDistance, sf::Vector2f minSize = {0, 0});
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		LayerWithConstBorder* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	typedef LayerWithConstBorder LayerWCBorder;
	typedef LayerWithConstBorder LWCBo;
}