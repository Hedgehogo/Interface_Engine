#pragma once
#include "../iLayer.h"
#include "../../iFlat.h"
#include "../../../../interaction/interactionStack/interactionStack.h"
#include <SFML/Graphics.hpp>

namespace ui {
	class LayerWithConstBorder : public ILayer {
	protected:
		IFlat *constObject;
		IFlat *secondObject;
		sf::Vector2f positionConstObject;
		sf::Vector2f sizeConstObject;
		float borderDistance;
		Side side;
		
		void init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelManager &overlayStack) override;
		
		void copy(LayerWithConstBorder* layerWithConstBorder);
	
	public:
		LayerWithConstBorder(IFlat *constObject, IFlat *secondObject, Side side, float borderDistance, sf::Vector2f minSize = {0, 0});

        ~LayerWithConstBorder() override;

		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void update() override;
		
		LayerWithConstBorder* copy() override;
	};
	
	typedef LayerWithConstBorder LayerWCBorder;
	typedef LayerWithConstBorder LWCBo;
}