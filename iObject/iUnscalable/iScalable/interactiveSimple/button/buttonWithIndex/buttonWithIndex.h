#pragma once
#include "../button.h"

namespace ui {
	class ButtonWithIndex : public Button {
	protected:
		uint16_t interactionIndex;
		
		void init(sf::RenderTarget &renderTarget, PanelManager &panelManager) override;
	
	public:
		ButtonWithIndex(ui::IDrawable *background, uint16_t interaction);
		
		ButtonWithIndex* copy() override;
	};
}
