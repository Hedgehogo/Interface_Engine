#pragma once

#include "../iLayout.hpp"
#include "../../iUnscalable/iScalable/iScalable.hpp"

namespace ui {
	class ILayoutWithObject : public virtual ILayout {
	public:
		struct Make : public virtual ILayout::Make {
			virtual ILayoutWithObject* make(InitInfo initInfo) = 0;
		};
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		virtual IScalable& getObject() = 0;
		
		virtual const IScalable& getObject() const = 0;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
