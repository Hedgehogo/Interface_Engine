#pragma once

#include "../iLayout.hpp"
#include "../../iUnscalable/iScalable/iScalable.hpp"

namespace ui {
	class ILayoutWithObjectsArray : public virtual ILayout {
	public:
		struct Make : public virtual ILayout::Make {
			virtual ILayoutWithObjectsArray* make(InitInfo initInfo) = 0;
		};
		
		void setPosition(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void setSize(sf::Vector2f size) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		virtual std::size_t getArraySize() const = 0;
		
		virtual IScalable& getObjectAt(std::size_t index) = 0;
		
		virtual const IScalable& getObjectAt(std::size_t index) const = 0;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
