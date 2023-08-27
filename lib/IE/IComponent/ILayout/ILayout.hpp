#pragma once

#include "../IComponent.hpp"

namespace ie {
	struct LayoutData {
		sf::Vector2f position{};
		sf::Vector2f size{};
		
		LayoutData();
		
		LayoutData(sf::Vector2f position, sf::Vector2f size);
		
		void setPosition(sf::Vector2f position);
		
		void move(sf::Vector2f position);
		
		void setSize(sf::Vector2f size);
		
		void resize(sf::Vector2f size, sf::Vector2f position);
	};
	
	class ILayout : public virtual IComponent {
	public:
		struct Make : public virtual IComponent::Make {
			virtual ILayout* make(InitInfo initInfo) = 0;
		};
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		sf::Vector2f getAreaPosition() const override;
		
		sf::Vector2f getAreaSize() const override;
		
		bool inArea(sf::Vector2f pointPosition) override;
		
	protected:
		virtual LayoutData& layoutGetData() = 0;
		
		virtual const LayoutData& layoutGetData() const = 0;
	};
}
