#pragma once
#include "../interactiveSimple.h"
#include "../../../iDrawn/iDrawn.h"

namespace ui {
	class Button : public Interactive_Simple {
	protected:
		ui::IFlat *background;
		
		void init(sf::RenderTarget &renderTarget, PanelManager &panelManager) override;
		
		void copy(Button* button);
		
	public:
		Button(IFlat *background, IInteraction* interaction);
		
		~Button() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getPosition() override;
		
		sf::Vector2f getSize() override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
	};
}