#pragma once

#include <SFML/Graphics.hpp>
#include "../interaction/interactionStack/interactionStack.h"
#include "../interaction/interactionManager/interactionManager.h"

namespace ui {
	class Panel;
	class PanelManager;
	
	class IObject {
	protected:
		virtual void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) = 0;
		
		void initObject(IObject *object, sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager);
		
	public:
		virtual ~IObject() = default;
		
		virtual void setPosition(sf::Vector2f position);
		
		virtual void move(sf::Vector2f position);
		
		virtual void setSize(sf::Vector2f size);
		
		virtual void draw() = 0;
		
		virtual void resize(sf::Vector2f size, sf::Vector2f position) = 0;
		
		virtual void update() = 0;
		
		virtual bool updateInteractions(sf::Vector2f mousePosition) = 0;
		
		virtual sf::Vector2f getPosition() = 0;
		
		virtual sf::Vector2f getAreaSize() = 0;
		
		virtual sf::Vector2f getSize();
		
		virtual sf::Vector2f getMinSize() = 0;
		
		virtual sf::Vector2f getNormalSize() = 0;
		
		virtual IObject* copy() = 0;

        virtual sf::Color HSVtoRGB(float H, float S = 1, float V = 1);
		
		virtual void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue = 0, uint hueOffset = 36);
	};
}