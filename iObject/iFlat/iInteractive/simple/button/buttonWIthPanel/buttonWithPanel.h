#pragma once
#include "../button.h"
#include "interaction/displayPanelInteraction.h"
#include "interaction/pointingDisplayPanelInteraction/pointingDisplayPanelInteraction.h"
#include "../../../../../panel/panel.h"
#include "../../../../../panel/interaction/pointingHidePanelInteraction/pointingHidePanelInteraction.h"

namespace ui {
	class ButtonWithPanel : public Button {
	protected:
		Panel *panel;
		
		void init(sf::RenderWindow &window, Panel *parent, PanelManager &panelStack) override;
		
	public:
		ButtonWithPanel(Panel *panel, DisplayPanelInteraction* interaction, IFlat *background);
		
		~ButtonWithPanel() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		ButtonWithPanel* copy() override;
	};
}
