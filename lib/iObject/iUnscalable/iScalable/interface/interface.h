#pragma once

#include <vector>
#include "../iScalable.h"
#include "../../../panel/panelManager/panelManager.h"
#include "../../../../interaction/interactionManager/interactionManager.h"
#include "../../../../interaction/interactionStack/interactionStack.h"
#include "../../../../interaction/event/wheel/wheelEvent.h"

namespace ui {
	class Interface : public IScalable {
	protected:
		sf::RenderWindow &window;
		sf::RenderTarget *renderTarget;
		InteractionStack* interactionStack;
		InteractionManager interactionManager;
		PanelManager panelManager;
		IScalable *object;
		bool initialized;
		
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		bool isInWindow(sf::Vector2f position);
		
	public:
		void init();
		
		Interface(IScalable *object, InteractionStack *interactionStack, sf::RenderWindow &window);
		
		~Interface() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getAreaPosition() override;
		
		sf::Vector2f getAreaSize() override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void updateCluster(sf::Vector2f mousePosition);
		
		void update() override;
		
		void update(int wheel);
		
		Interface* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue = 0, uint hueOffset = 36) override;
	};
}
