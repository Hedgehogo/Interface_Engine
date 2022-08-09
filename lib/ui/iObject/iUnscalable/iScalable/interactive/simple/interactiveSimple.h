#pragma once
#include "../../../interactive/interactive.h"

namespace ui {
	class Interactive_Simple : public virtual IScalable, public Interactive, public IUpdatable {
	private:
		bool interact;
		bool oldInteract;
		
	protected:
		IInteraction* interaction;
		
		void copy(Interactive_Simple* interactive_Simple);
		
	public:
		explicit Interactive_Simple(IInteraction* interaction);
		
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, PanelManager &panelManager) override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
	};
}