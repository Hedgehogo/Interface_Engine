#pragma once
#include "../button.h"

namespace ui {
	class ButtonWithIndex : public Button {
	protected:
		uint16_t interactionIndex;
		
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, PanelManager &panelManager) override;
	
	public:
		ButtonWithIndex(ui::OnlyDrawable *background, uint16_t interaction);
		
		ButtonWithIndex* copy() override;
	};
}
