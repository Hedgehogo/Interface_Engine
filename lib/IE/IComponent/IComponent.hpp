#pragma once

#include "../IDrawable/DrawManager/DrawManager.hpp"
#include "../IUpdatable/UpdateManager/UpdateManager.hpp"
#include "../Interaction/InteractionStack/InteractionStack.hpp"
#include "../Interaction/InteractionManager/InteractionManager.hpp"
#include "../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include "../Animation/AnimationManager/AnimationManager.hpp"
#include "../Make/make.hpp"
#include "InitInfo/InitInfo.hpp"

using uint = unsigned;

namespace ui {
	using namespace bp;
	
	class Panel;
	
	class PanelManager;
	
	class IPanelManager;
	
	class IComponent {
	public:
		struct Make {
			virtual IComponent* make(InitInfo initInfo) = 0;
			
			virtual ~Make() = default;
		};
		
		virtual ~IComponent() = default;
		
		virtual void init(InitInfo initInfo) = 0;
		
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
		
		virtual IComponent* copy() = 0;
		
		static void drawDebug(sf::Vector2f position, sf::Vector2f size, sf::RenderTarget& renderTarget, uint hue);
		
		virtual void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset);
	};
	
	template<typename T>
	sf::Vector2<T> max(const sf::Vector2<T>& first, const sf::Vector2<T>& second) {
		return {std::max(first.x, second.x), std::max(first.y, second.y)};
	}
	
	template<typename T>
	sf::Vector2<T> max(const sf::Vector2<T>& first, const sf::Vector2<T>& second, const sf::Vector2<T>& third) {
		return {std::max(first.x, std::max(second.x, third.x)), std::max(first.y, std::max(second.y, third.y))};
	}
	
	std::vector<float>& addBounds(std::vector<float>& vector);
	
	std::vector<float> genBounds(std::size_t size);
	
	template<typename T>
	std::size_t y_size(std::vector<std::vector<T> >& vector) {
		if(vector.empty()) {
			return 0;
		}
		return vector[0].size();
	}
	
	namespace detail {
		template<typename T>
		void addItems(std::vector<T>&) {
		}
		
		template<typename T, typename A, typename... As>
		void addItems(std::vector<T>& vector, A&& arg, As&& ... args) {
			vector.emplace_back(std::move(arg));
			addItems<T, As...>(vector, std::move(args)...);
		}
	}
	
	template<typename T, typename... As>
	std::vector<T> makeVector(T&& arg, As&&... args) {
		std::vector<T> result;
		result.reserve(sizeof...(As) + 1);
		detail::addItems<T, As...>(result, std::move(arg), std::move(args)...);
		return result;
	}
	
	template<typename T, T (* f)(T)>
	sf::Vector2<T> mapVector2(sf::Vector2<T> value) {
		return {f(value.x), f(value.y)};
	}
}