#pragma once
#include "../iLayer.h"
#include "../../iScalable.h"
#include "../../../../../interaction/interactionStack/interactionStack.h"
#include <SFML/Graphics.hpp>

namespace ui {
	class LayerWithConstBorder : public ILayer {
	protected:
		IScalable *constObject;
		IScalable *secondObject;
		sf::Vector2f positionConstObject;
		sf::Vector2f sizeConstObject;
		float borderDistance;
		Side side;
		
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		void copy(LayerWithConstBorder* layerWithConstBorder);
	
	public:
		LayerWithConstBorder(IScalable *constObject, IScalable *secondObject, Side side, float borderDistance, sf::Vector2f minSize = {0, 0});

        ~LayerWithConstBorder() override;

		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void update() override;
		
		LayerWithConstBorder* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	typedef LayerWithConstBorder LayerWCBorder;
	typedef LayerWithConstBorder LWCBo;
}