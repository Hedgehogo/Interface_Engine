#pragma once

#include "IE/layout/ILayout/ILayout.hpp"
#include "../IComponent.hpp"

namespace ie {
	class IComponentLayout : public virtual ILayout, public virtual IComponent {
	public:
		struct Make : public virtual IComponent::Make {
			virtual IComponentLayout* make(InitInfo initInfo) = 0;
		};
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		sf::Vector2f getAreaPosition() const override;
		
		sf::Vector2f getAreaSize() const override;
		
		bool inArea(sf::Vector2f pointPosition) override;
	};
}
