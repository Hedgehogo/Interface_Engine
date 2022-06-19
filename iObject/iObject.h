#pragma once

#include <SFML/Graphics.hpp>
#include "../interaction/interactionStack/interactionStack.h"
#include "../interaction/interactionManager/interactionManager.h"

namespace ui {
	class Panel;
	class PanelStack;
	
	class IObject {
	protected:
		virtual void init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelStack &panelStack) = 0;
		
		void initObject(IObject *object, sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelStack &overlayStack);
		
	public:
		virtual ~IObject() = default;
		
		virtual void draw() = 0;
		
		virtual void resize(sf::Vector2f size, sf::Vector2f position) = 0;
		
		virtual void update() = 0;
		
		virtual bool updateInteractions(sf::Vector2f mousePosition) = 0;
		
		virtual sf::Vector2f getMinSize() = 0;
		
		virtual sf::Vector2f getNormalSize() = 0;
		
		virtual IObject* copy() = 0;
	};
}