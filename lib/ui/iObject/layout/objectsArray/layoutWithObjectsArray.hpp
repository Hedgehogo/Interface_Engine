#pragma once
#include "../layout.hpp"
#include "../../iUnscalable/iScalable/iScalable.hpp"

namespace ui {
	class LayoutWithObjectsArray : public virtual Layout {
	protected:
		std::vector<IScalable*> objects;
	
	public:
		void init(InitInfo initInfo) override;
		
		explicit LayoutWithObjectsArray(std::vector<IScalable*> objects);
		
		~LayoutWithObjectsArray() override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;

		virtual uint getArraySize();

		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
