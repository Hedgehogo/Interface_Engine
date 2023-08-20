#pragma once

#include "../iLayout.hpp"
#include "../objectsArray/iLayoutWithObjectsArray.hpp"

namespace ui {
	class ILayoutWithTwoObjects : public virtual ILayoutWithObjectsArray {
	public:
		struct Make : public virtual ILayoutWithObjectsArray::Make {
			virtual ILayoutWithTwoObjects* make(InitInfo initInfo) = 0;
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
