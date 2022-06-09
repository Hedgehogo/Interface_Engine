#pragma once
#include "../button.h"

namespace ui {
	class ButtonWithIndex : public Button {
	protected:
		uint16_t interactionIndex;
		
		void init(sf::RenderWindow &window, Panel *parent, PanelStack &overlayStack) override;
	
	public:
		ButtonWithIndex(ui::IDrawn *background, uint16_t interaction);
	};
}
