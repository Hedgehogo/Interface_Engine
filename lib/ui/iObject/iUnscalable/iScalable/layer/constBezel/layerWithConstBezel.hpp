#pragma once

#include "../layer.hpp"
#include "../../uninteractive/unIteractive.hpp"
#include "../../../../layout/object/layoutWithObject.h"
#include "../../../../../interaction/interactionStack/interactionStack.h"
#include "../../../../../interaction/interactionManager/interactionManager.h"

namespace ui {
	class LayerWithConstBezel : public Layer, public LayoutWithObject {
	protected:
		IUninteractive *bezel;
		float thickness;
		
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;
		
		LayerWithConstBezel(IScalable *object, IUninteractive *bezel, float thickness, sf::Vector2f minSize = {0, 0});
		
		~LayerWithConstBezel() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		LayerWithConstBezel* copy() override;
		
		static LayerWithConstBezel* createFromYaml(const YAML::Node &node);
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	typedef LayerWithConstBezel LayerWCBezel;
	typedef LayerWithConstBezel LWCBe;
}
