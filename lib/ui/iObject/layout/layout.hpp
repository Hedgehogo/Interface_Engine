#pragma once

#include "../iObject.hpp"

namespace ui {
	class Layout : public virtual IObject {
	protected:
		sf::Vector2f position;
		sf::Vector2f size;
		
		void copy(Layout* layout);
	
	public:
		explicit Layout(sf::Vector2f size = {});
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		sf::Vector2f getAreaPosition() const override;
		
		sf::Vector2f getPosition() const override;
		
		sf::Vector2f getAreaSize() const override;
		
		sf::Vector2f getSize() const override;
		
		bool inArea(sf::Vector2f pointPosition) override;
		
		bool in(sf::Vector2f pointPosition) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
	};
}
