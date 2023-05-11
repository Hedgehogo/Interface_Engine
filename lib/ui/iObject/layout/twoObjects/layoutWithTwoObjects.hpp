#pragma once

#include "../layout.hpp"
#include "../../iUnscalable/iScalable/iScalable.hpp"

namespace ui {
	class LayoutWithTwoObjects : public virtual Layout {
	protected:
		IScalable* firstObject;
		IScalable* secondObject;
	
	public:
		void init(InitInfo initInfo) override;
		
		explicit LayoutWithTwoObjects(IScalable* firstObject, IScalable* secondObject);
		
		~LayoutWithTwoObjects() override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
