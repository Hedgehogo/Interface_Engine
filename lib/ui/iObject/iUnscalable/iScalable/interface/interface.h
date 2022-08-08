#pragma once

#include <vector>
#include "../iScalable.hpp"
#include "../../../panel/manager/panelManager.h"
#include "../../../../interaction/interactionManager/interactionManager.h"
#include "../../../../interaction/interactionStack/interactionStack.h"
#include "../../../../interaction/event/wheel/wheelEvent.h"

namespace ui {
	class Interface : public IScalable, public IDrawable, public IUpdatable {
	protected:
		sf::RenderTarget *renderTarget;
		DrawManager drawManager;
		UpdateManager updateManager;
		InteractionManager interactionManager;
		InteractionStack* interactionStack;
		PanelManager panelManager;
		IScalable *object;
		sf::Vector2f mousePosition;
		bool initialized;
		bool active;
		
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;
		
		bool isInWindow(sf::Vector2f position);
		
	public:
		void init(sf::RenderTarget &renderTarget);
		
		Interface(IScalable *object, InteractionStack *interactionStack);
		
		~Interface() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getAreaPosition() override;
		
		sf::Vector2f getAreaSize() override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
	protected:
		void updateCluster(sf::Vector2f mousePosition);
		
		void update() override;
		
	public:
		void update(sf::Vector2f mousePosition, bool active);
		
		Interface* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue = 0, uint hueOffset = 36) override;
	};
}
