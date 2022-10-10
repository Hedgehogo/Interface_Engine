#pragma once

#include "../layer.hpp"
#include "../../uninteractive/uninteractive.hpp"
#include "../../../../layout/object/layoutWithObject.hpp"
#include "../../../../../interaction/interactionStack/interactionStack.hpp"
#include "../../../../../interaction/interactionManager/interactionManager.hpp"

namespace ui {
	class LayerWithConstBezel : public Layer, public LayoutWithObject {
	protected:
		IUninteractive *bezel;
		float thickness;
		
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) override;
		
		LayerWithConstBezel(IScalable *object, IUninteractive *bezel, float thickness, sf::Vector2f minSize = {0, 0});
		
		~LayerWithConstBezel() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		LayerWithConstBezel* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	bool convertPointer(const YAML::Node &node, LayerWithConstBezel *&layerWithConstBezel);
	
	typedef LayerWithConstBezel LayerWCBezel;
	typedef LayerWithConstBezel LWCBe;
}
