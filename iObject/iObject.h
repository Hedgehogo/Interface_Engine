#pragma once

#include <SFML/Graphics.hpp>
#include "../interaction/interactionStack/interactionStack.h"
#include "../interaction/interactionManager/interactionManager.h"

typedef unsigned uint;

namespace ui {
	class Panel;
	class PanelManager;
	
	class IObject {
	public:
		virtual void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) = 0;
		
		void initObject(IObject *object, sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager);
		
		virtual ~IObject() = default;
		
		virtual void setPosition(sf::Vector2f position);
		
		virtual void move(sf::Vector2f position);
		
		virtual void setSize(sf::Vector2f size);
		
		virtual sf::Vector2f getAreaPosition() = 0;
		
		virtual sf::Vector2f getPosition();
		
		virtual sf::Vector2f getAreaSize() = 0;
		
		virtual sf::Vector2f getSize();
		
		virtual sf::Vector2f getMinSize() = 0;
		
		virtual sf::Vector2f getNormalSize() = 0;
		
		virtual bool inArea(sf::Vector2f pointPosition);
		
		virtual bool in(sf::Vector2f pointPosition);
		
		virtual void draw() = 0;
		
		virtual void resize(sf::Vector2f size, sf::Vector2f position) = 0;
		
		virtual void update() = 0;
		
		virtual bool updateInteractions(sf::Vector2f mousePosition) = 0;
		
		virtual IObject* copy() = 0;

        static sf::Color HSVtoRGB(float H, float S = 1, float V = 1);
		
		virtual void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset);
	};
}