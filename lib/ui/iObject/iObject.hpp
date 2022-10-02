#pragma once

#include <SFML/Graphics.hpp>
#include "../drawable/manager/drawManager.hpp"
#include "../updatable/manager/updateManager.hpp"
#include "../interaction/interactionStack/interactionStack.hpp"
#include "../interaction/interactionManager/interactionManager.hpp"
#include "../../yaml/yamlWithSfml/yamlBuilder/yamlBuilder.hpp"

typedef unsigned uint;

namespace ui {
	class Panel;
	class PanelManager;
	class IPanelManager;
	
	class IObject {
	public:
		virtual void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) = 0;
		
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
		
		virtual void resize(sf::Vector2f size, sf::Vector2f position) = 0;
		
		virtual bool updateInteractions(sf::Vector2f mousePosition) = 0;
		
		virtual IObject* copy() = 0;
		
        static sf::Color HSVtoRGB(float H, float S = 1, float V = 1);

        static void drawDebug(sf::Vector2f position, sf::Vector2f size, sf::RenderTarget &renderTarget, uint hue);

		virtual void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset);
	};
	
	template<typename T>
	sf::Vector2<T> max(const sf::Vector2<T>& first, const sf::Vector2<T>& second) {
		return {std::max(first.x, second.x), std::max(first.y, second.y)};
	}
	
	template<typename T>
	sf::Vector2<T> max(const sf::Vector2<T>& first, const sf::Vector2<T>& second, const sf::Vector2f& third) {
		return {std::max({first.x, second.x, third.x}), std::max({first.y, second.y, third.y})};
	}
}