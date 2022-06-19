#pragma once
#include <vector>
#include "../iLayer.h"
#include "../../../../interaction/interactionStack/interactionStack.h"

namespace ui {
	class LayerWithBorder : public ILayer {
	protected:
		std::vector<std::vector<IFlat *>> objects;
		std::vector<float> boundsVertical;
		std::vector<float> boundsHorizontal;
		
		void init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelStack &overlayStack) override;
	
	public:
		LayerWithBorder(std::vector<std::vector<IFlat *>> objects, std::vector<float> boundsHorizontal, std::vector<float> boundsVertical, sf::Vector2f minSize = {0, 0});
		
		~LayerWithBorder() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void update() override;
		
		LayerWithBorder* copy() override;
	};
	
	typedef LayerWithBorder LayerWBorder;
	typedef LayerWithBorder LWB;
}

