#pragma once

#include "../IComponentLayout.hpp"
#include "IE/layout/ILayout/ILayoutBackground/ILayoutBackground.hpp"

namespace ie {
	class IComponentBackground : public virtual IComponentLayout, public virtual ILayoutBackground {
	public:
		struct Make : public virtual IComponentLayout::Make {
			virtual IComponentBackground* make(InitInfo initInfo) = 0;
		};
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
