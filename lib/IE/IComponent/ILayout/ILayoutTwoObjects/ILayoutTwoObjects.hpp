#pragma once

#include "../ILayout.hpp"
#include "../ILayoutObjectsArray/ILayoutObjectsArray.hpp"

namespace ie {
	class ILayoutTwoObjects : public virtual ILayoutObjectsArray {
	public:
		struct Make : public virtual ILayoutObjectsArray::Make {
			virtual ILayoutTwoObjects* make(InitInfo initInfo) = 0;
		};
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		std::size_t getArraySize() const override;
		
		IScalable& getObjectAt(std::size_t index) override;
		
		const IScalable& getObjectAt(std::size_t index) const override;
		
		virtual IScalable& getFirstObject() = 0;
		
		virtual IScalable& getSecondObject() = 0;
		
		virtual const IScalable& getFirstObject() const = 0;
		
		virtual const IScalable& getSecondObject() const = 0;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
