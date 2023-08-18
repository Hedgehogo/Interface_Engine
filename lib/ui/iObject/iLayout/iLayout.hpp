#pragma once

#include "../iObject.hpp"

namespace ui {
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
	
	class ILayout : public virtual IObject {
	public:
		struct Make : public virtual IObject::Make {
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
