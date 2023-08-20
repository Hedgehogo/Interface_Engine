#pragma once

#include "../iLayout.hpp"
#include "../../iUnscalable/iScalable/uninteractive/uninteractive.hpp"

namespace ui {
	class ILayoutWithBackground : public virtual ILayout {
	public:
		struct Make : public virtual ILayout::Make {
			virtual ILayoutWithBackground* make(InitInfo initInfo) = 0;
		};
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		virtual IUninteractive& getBackground() = 0;
		
		virtual const IUninteractive& getBackground() const = 0;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
