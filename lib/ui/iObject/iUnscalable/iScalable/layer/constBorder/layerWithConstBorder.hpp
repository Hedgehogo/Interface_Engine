#pragma once
#include "../layer.hpp"
#include "../../iScalable.hpp"
#include "../../../../layout/twoObjects/layoutWithTwoObjects.hpp"
#include "../../../../../interaction/interactionStack/interactionStack.hpp"
#include "../../../../../enums/side/side.hpp"

namespace ui {
	class LayerWithConstBorder : public Layer, public LayoutWithTwoObjects {
	protected:
		float borderDistance;
		Side side;
	
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) override;
		
		LayerWithConstBorder(IScalable *constObject, IScalable *secondObject, Side side, float borderDistance, sf::Vector2f minSize = {0, 0});
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		LayerWithConstBorder* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	bool convertPointer(const YAML::Node &node, LayerWithConstBorder *&layerWithConstBorder);
	
	typedef LayerWithConstBorder LayerWCBorder;
	typedef LayerWithConstBorder LWCBo;
}