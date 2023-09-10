#pragma once

#include "../IComponentObjectsArray/IComponentObjectsArray.hpp"
#include "IE/ILayout/ILayoutTwoObjects/ILayoutTwoObjects.hpp"

namespace ie {
	class IComponentTwoObjects : public virtual IComponentObjectsArray, public virtual ILayoutTwoObjects{
	public:
		struct Make : public virtual IComponentObjectsArray::Make {
			virtual IComponentTwoObjects* make(InitInfo initInfo) = 0;
		};
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
