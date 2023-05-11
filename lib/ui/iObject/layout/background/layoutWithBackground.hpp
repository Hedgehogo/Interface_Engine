#pragma once

#include "../layout.hpp"
#include "../../iUnscalable/iScalable/uninteractive/uninteractive.hpp"

namespace ui {
	class LayoutWithBackground : public virtual Layout {
	protected:
		IUninteractive* background;
	
	public:
		void init(InitInfo initInfo) override;
		
		explicit LayoutWithBackground(IUninteractive* background);
		
		~LayoutWithBackground() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
