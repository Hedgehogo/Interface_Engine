#pragma once
#include "../baseButton.hpp"

namespace ui {
	class Button : public BaseButton {
	protected:
		uint16_t interactionIndex;
		
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, PanelManager &panelManager) override;
	
	public:
		Button(ui::OnlyDrawable *background, uint16_t interaction);
		
		Button* copy() override;

        static Button* createFromYaml(const YAML::Node &node);
	};
}
