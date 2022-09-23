#pragma once
#include "../baseButton.hpp"

namespace ui {
	class Button : public BaseButton {
	protected:
		int interactionIndex;
	
	public:
		Button(ui::IUninteractive *background, int interaction);

		Button(ui::IUninteractive *background, IInteraction *interaction);

		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, IPanelManager &panelManager) override;

		Button* copy() override;

        static Button* createFromYaml(const YAML::Node &node);
	};
}
