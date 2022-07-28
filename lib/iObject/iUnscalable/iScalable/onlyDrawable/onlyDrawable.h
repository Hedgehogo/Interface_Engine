#pragma once
#include <SFML/Graphics.hpp>

#include "../iScalable.h"
#include "../../../../drawable/iDrawable/iDrawable.h"
#include "../../../../interaction/interactionStack/interactionStack.h"

namespace ui {
	class OnlyDrawable : public IScalable, public IDrawable {
	protected:
		sf::RenderTarget *renderTarget;

		void copy(OnlyDrawable* onlyDrawable);
		
	public:
		OnlyDrawable();

        void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;

        void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		void draw() override = 0;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override = 0;
		
		sf::Vector2f getMinSize() override = 0;
		
		sf::Vector2f getNormalSize() override = 0;
		
		OnlyDrawable* copy() override = 0;
	};
}
