#pragma once

#include "../layout.hpp"
#include "../../iUnscalable/iScalable/iScalable.hpp"

namespace ui {
	class LayoutWithObjectsArray : public virtual Layout {
	public:
		void init(InitInfo initInfo) override;
		
		explicit LayoutWithObjectsArray(std::vector<IScalable*> objects);
		
		~LayoutWithObjectsArray() override;
		
		void move(sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		virtual uint getArraySize();
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	
	protected:
		std::vector<IScalable*> objects;
	};
}
