#pragma once

#include "../iLayout.hpp"
#include "../../iUnscalable/iScalable/iScalable.hpp"

namespace ui {
	class ILayoutWithObjectsArray : public virtual ILayout {
	public:
		void move(sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		virtual std::size_t getArraySize() const = 0;
		
		virtual IScalable& getObjectAt(std::size_t index) = 0;
		
		virtual const IScalable& getObjectAt(std::size_t index) const = 0;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
