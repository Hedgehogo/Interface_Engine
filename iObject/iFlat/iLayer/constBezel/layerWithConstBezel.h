#pragma once

#include "../iLayer.h"
#include "../../iDrawn/iDrawn.h"
#include "../../../../interaction/interactionStack/interactionStack.h"
#include "../../../../interaction/interactionManager/interactionManager.h"

namespace ui {
	class LayerWithConstBezel : public ILayer {
	protected:
		IFlat *object;
		IDrawn *bezel;
		float thickness;
		
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
	public:
		LayerWithConstBezel(IFlat *object, IDrawn *bezel, float thickness, sf::Vector2f minSize = {0, 0});
		
		~LayerWithConstBezel() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void update() override;
		
		LayerWithConstBezel* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	typedef LayerWithConstBezel LayerWCBezel;
	typedef LayerWithConstBezel LWCBe;
}
