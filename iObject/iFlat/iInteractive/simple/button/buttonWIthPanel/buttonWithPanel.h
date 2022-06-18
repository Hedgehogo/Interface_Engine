#pragma once
#include "../button.h"
#include "interaction/displayPanelInteraction.h"
#include "interaction/pointingDisplayPanelInteraction/pointingDisplayPanelInteraction.h"

namespace ui {
	class ButtonWithPanel : public Button {
	protected:
		Panel *panel;
		
		void init(sf::RenderWindow &window, Panel *parent, PanelStack &panelStack) override;
		
	public:
		ButtonWithPanel(Panel *panel, DisplayPanelInteraction* interaction, IFlat *background);
		
		~ButtonWithPanel() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		ButtonWithPanel* copy() override;
	};
}
