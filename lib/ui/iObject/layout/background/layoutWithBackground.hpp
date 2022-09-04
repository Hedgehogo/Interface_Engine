#pragma once
#include "../layout.hpp"
#include "../../iUnscalable/iScalable/uninteractive/uninteractive.hpp"
#include "../../../drawable/manager/drawManager.hpp"

namespace ui {
	class LayoutWithBackground : public virtual Layout {
	protected:
		IUninteractive* background;
		
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;
		
		explicit LayoutWithBackground(IUninteractive* background);
		
		~LayoutWithBackground() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
