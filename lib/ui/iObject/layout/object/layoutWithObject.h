#pragma once
#include "../layout.h"
#include "../../iUnscalable/iScalable/iScalable.hpp"

namespace ui {
	class LayoutWithObject : public virtual Layout {
	protected:
		IScalable* object;
		
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;
		
		explicit LayoutWithObject(IScalable* object);
		
		~LayoutWithObject() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
