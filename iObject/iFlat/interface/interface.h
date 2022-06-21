#pragma once

#include <vector>
#include "../iFlat.h"
#include "../../panel/panelManager/panelManager.h"
#include "../../../interaction/interactionManager/interactionManager.h"
#include "../../../interaction/interactionStack/interactionStack.h"
#include "../../../interaction/event/wheel/wheelEvent.h"

namespace ui {
	class Interface : public IFlat {
	protected:
		sf::RenderWindow &window;
		InteractionStack* interactionStack;
		InteractionManager interactionManager;
		PanelManager panelManager;
		IFlat *object;
		bool initialized;
		
		void init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		bool isInWindow(sf::Vector2f position);
		
	public:
		void init();
		
		Interface(IFlat *object, InteractionStack *interactionStack, sf::RenderWindow &window);
		
		~Interface() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getPosition() override;
		
		sf::Vector2f getSize() override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void updateCluster(sf::Vector2f mousePosition);
		
		void update() override;
		
		void update(int wheel);
		
		Interface* copy() override;
	};
}
