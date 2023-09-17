#pragma once

#include "../IComponentLayout.hpp"
#include "IE/ILayout/ILayoutObjectsArray/ILayoutObjectsArray.hpp"

namespace ie {
	class IComponentObjectsArray : public virtual IComponentLayout, public virtual ILayoutObjectsArray {
	public:
		struct Make : public virtual IComponentLayout::Make {
			virtual IComponentObjectsArray* make(InitInfo initInfo) = 0;
		};
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
