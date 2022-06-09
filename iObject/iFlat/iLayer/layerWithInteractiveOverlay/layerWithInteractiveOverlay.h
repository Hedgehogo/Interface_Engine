#pragma once

#include "../iLayer.h"
#include "../../iDrawn/iDrawn.h"
#include "../../../panel/panel.h"
#include "../../../panel/panelStack/panelStack.h"
#include "../../../../interaction/interactionManager/interactionManager.h"
#include "../../../../interaction/interactionStack/interactionStack.h"


namespace ui {
	class LayerWithInteractiveOverlay : public ILayer {
	protected:
		PanelStack *panelStack;
		Panel *panel;
		IFlat *object;
		
		void init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelStack &panelStack) override;
		
	public:
		LayerWithInteractiveOverlay(Panel *panel, IFlat *object);
		
		~LayerWithInteractiveOverlay() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
	};
}