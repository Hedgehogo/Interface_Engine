#pragma once
#include "../interactiveSimple.h"
#include "../../../onlyDrawable/onlyDrawable.hpp"

namespace ui {
	class Button : public Interactive_Simple {
	protected:
		ui::IScalable *background;
		
		void copy(Button* button);
		
	public:
		Button(IScalable *background, IInteraction* interaction);

		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, PanelManager &panelManager) override;

		~Button() override;

		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getAreaPosition() override;
		
		sf::Vector2f getAreaSize() override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;

        bool updateInteractions(sf::Vector2f mousePosition) override;

		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}