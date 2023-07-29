#pragma once

#include "../drawable/manager/drawManager.hpp"
#include "../updatable/manager/updateManager.hpp"
#include "../interaction/interactionStack/interactionStack.hpp"
#include "../interaction/interactionManager/interactionManager.hpp"
#include "../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "../animation/manager/animationManager.hpp"
#include "initInfo/initInfo.hpp"

using uint = unsigned;

namespace ui {
	using namespace bp;
	
	class Panel;
	
	class PanelManager;
	
	class IPanelManager;
	
	class IObject {
	public:
		virtual void init(InitInfo initInfo) = 0;
		
		virtual ~IObject() = default;
		
		virtual void setPosition(sf::Vector2f position);
		
		virtual void move(sf::Vector2f position);
		
		virtual void setSize(sf::Vector2f size);
		
		virtual sf::Vector2f getAreaPosition() const = 0;
		
		virtual sf::Vector2f getPosition() const;
		
		virtual sf::Vector2f getAreaSize() const = 0;
		
		virtual sf::Vector2f getSize() const;
		
		virtual sf::Vector2f getMinSize() const = 0;
		
		virtual sf::Vector2f getNormalSize() const = 0;
		
		virtual bool inArea(sf::Vector2f pointPosition);
		
		virtual bool in(sf::Vector2f pointPosition);
		
		virtual void resize(sf::Vector2f size, sf::Vector2f position) = 0;
		
		virtual bool updateInteractions(sf::Vector2f mousePosition) = 0;
		
		virtual IObject* copy() = 0;
		
		static void drawDebug(sf::Vector2f position, sf::Vector2f size, sf::RenderTarget& renderTarget, uint hue);
		
		virtual void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset);
	};
	
	template<typename T>
	sf::Vector2<T> max(const sf::Vector2<T>& first, const sf::Vector2<T>& second) {
		return {std::max(first.x, second.x), std::max(first.y, second.y)};
	}
	
	template<typename T>
	sf::Vector2<T> max(const sf::Vector2<T>& first, const sf::Vector2<T>& second, const sf::Vector2f& third) {
		return {std::max({first.x, second.x, third.x}), std::max({first.y, second.y, third.y})};
	}
	
	template<typename T>
	auto copy(const std::vector<T*>& vec) -> std::vector<T*>{
		std::vector<T*> result(vec.size());
		for(int i = 0; i < vec.size(); ++i) {
			result[i] = vec[i]->copy();
		}
		return result;
	}
}