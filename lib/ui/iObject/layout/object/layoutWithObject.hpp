#pragma once

#include "../layout.hpp"
#include "../../iUnscalable/iScalable/iScalable.hpp"

namespace ui {
	class LayoutWithObject : public virtual Layout {
	protected:
		IScalable* object;
	
	public:
		void init(InitInfo initInfo) override;
		
		explicit LayoutWithObject(IScalable* object);
		
		~LayoutWithObject() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
