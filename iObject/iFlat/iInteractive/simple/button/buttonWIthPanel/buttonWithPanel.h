#pragma once
#include "../button.h"
#include "../../../../../panel/panel.h"
#include "../../../../../panel/interaction/display/pointing/pointingDisplayPanelInteraction.h"
#include "../../../../../panel/interaction/hide/pointing/pointingHidePanelInteraction.h"
#include "../../../../../panel/interaction/hide/click/clickHidePanelInteraction.h"

namespace ui {
	class ButtonWithPanel : public Button {
	protected:
		Panel *panel;
		
		void init(sf::RenderTarget &renderTarget, PanelManager &panelManager) override;
		
	public:
		ButtonWithPanel(Panel *panel, DisplayPanelInteraction* interaction, IFlat *background);
		
		~ButtonWithPanel() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		ButtonWithPanel* copy() override;
	};
}
