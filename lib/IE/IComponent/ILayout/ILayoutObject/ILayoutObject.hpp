#pragma once

#include "../ILayout.hpp"
#include "../../IUnscalable/IScalable/IScalable.hpp"

namespace ie {
	class ILayoutObject : public virtual ILayout {
	public:
		struct Make : public virtual ILayout::Make {
			virtual ILayoutObject* make(InitInfo initInfo) = 0;
		};
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		virtual IScalable& getObject() = 0;
		
		virtual const IScalable& getObject() const = 0;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
