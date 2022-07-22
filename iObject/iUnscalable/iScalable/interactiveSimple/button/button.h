#pragma once
#include "../interactiveSimple.h"
#include "../../iDrawable/iDrawable.h"

namespace ui {
	class Button : public Interactive_Simple {
	protected:
		ui::IScalable *background;
		
		void init(sf::RenderTarget &renderTarget, PanelManager &panelManager) override;
		
		void copy(Button* button);
		
	public:
		Button(IScalable *background, IInteraction* interaction);
		
		~Button() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getAreaPosition() override;
		
		sf::Vector2f getAreaSize() override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}