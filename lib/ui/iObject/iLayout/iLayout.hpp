#pragma once

#include "../iObject.hpp"

namespace ui {
	struct LayoutData {
		sf::Vector2f position{};
		sf::Vector2f size{};
		
		LayoutData();
		
		LayoutData(sf::Vector2f position, sf::Vector2f size);
	};
	
	class ILayout : public virtual IObject {
	public:
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		sf::Vector2f getAreaPosition() const override;
		
		sf::Vector2f getAreaSize() const override;
		
		virtual LayoutData& getLayoutData() = 0;
		
		virtual const LayoutData& getLayoutData() const = 0;
		
		sf::Vector2f& getLayoutPosition();
		
		sf::Vector2f& getLayoutSize();
		
		const sf::Vector2f& getLayoutPosition() const;
		
		const sf::Vector2f& getLayoutSize() const;
		
		bool inArea(sf::Vector2f pointPosition) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
	};
}
