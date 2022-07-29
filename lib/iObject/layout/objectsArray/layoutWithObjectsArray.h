#pragma once
#include "../layout.h"
#include "../../iUnscalable/iScalable/iScalable.h"

namespace ui {
	class LayoutWithObjectsArray : public virtual Layout {
	protected:
		std::vector<IScalable*> objects;
	
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;
		
		explicit LayoutWithObjectsArray(std::vector<IScalable*> objects);
		
		~LayoutWithObjectsArray() override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
