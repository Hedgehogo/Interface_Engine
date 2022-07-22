#pragma once
#include <vector>

#include "../iLayer.h"
#include "../../../../layout/objectsArray/layoutWithObjectsArray.h"
#include "../../../../../interaction/interactionStack/interactionStack.h"
#include "../../../../../interaction/interactionManager/interactionManager.h"

namespace ui {
	class LayerWithBorderVertical : public ILayer, public LayoutWithObjectsArray {
	protected:
		std::vector<float> boundsVertical;
		
	public:
		LayerWithBorderVertical(std::vector<IScalable *> objects, std::vector<float> boundsVertical, sf::Vector2f minSize = {0, 0});
		
		LayerWithBorderVertical(std::vector<IScalable *> objects, sf::Vector2f minSize = {0, 0});
		
		LayerWithBorderVertical(IScalable *first, IScalable *second, float bound = 0.5f, sf::Vector2f minSize = {0, 0});
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		LayerWithBorderVertical* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	typedef LayerWithBorderVertical LayerWBoundV;
	typedef LayerWithBorderVertical LWBV;
}
