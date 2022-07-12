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
		
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
	
	public:
		LayerWithBorder(std::vector<std::vector<IFlat *>> objects, std::vector<float> boundsHorizontal, std::vector<float> boundsVertical, sf::Vector2f minSize = {0, 0});
		
		LayerWithBorder(std::vector<std::vector<IFlat *>> objects, sf::Vector2f minSize = {0, 0});
		
		~LayerWithBorder() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void update() override;
		
		LayerWithBorder* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	typedef LayerWithBorder LayerWBorder;
	typedef LayerWithBorder LWB;
}

