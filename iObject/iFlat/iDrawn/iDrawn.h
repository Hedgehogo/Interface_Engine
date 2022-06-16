#pragma once
#include <SFML/Graphics.hpp>

#include "../iFlat.h"
#include "../../../interaction/interactionStack/interactionStack.h"

namespace ui {
	class IDrawn : public IFlat {
	protected:
		sf::RenderWindow *window;
		
		void init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelManager &overlayStack) override;
		
		void copy(IDrawn* iDrawn);
		
	public:
		IDrawn();
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		void draw() override = 0;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override = 0;
		
		sf::Vector2f getMinSize() override = 0;
		
		sf::Vector2f getNormalSize() override = 0;
		
		IDrawn* copy() override = 0;
	};
}
