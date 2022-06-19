#pragma once
#include <vector>

#include "../iLayer.h"
#include "../../../../interaction/interactionStack/interactionStack.h"
#include "../../../../interaction/interactionManager/interactionManager.h"

namespace ui {
	class LayerWithBorderVertical : public ILayer {
	protected:
		std::vector<IFlat *> objects;
		std::vector<float> boundsVertical;
		
		void init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
	public:
		LayerWithBorderVertical(std::vector<IFlat *> objects, std::vector<float> boundsVertical, sf::Vector2f minSize = {0, 0});
		
		LayerWithBorderVertical(std::vector<IFlat *> objects, sf::Vector2f minSize = {0, 0});
		
		~LayerWithBorderVertical() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void update() override;
		
		LayerWithBorderVertical* copy() override;
	};
	
	typedef LayerWithBorderVertical LayerWBoundV;
	typedef LayerWithBorderVertical LWBV;
}
