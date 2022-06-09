#pragma once
#include "../iInteractive.h"

namespace ui {
	class Interactive_Simple : public IInteractive {
	private:
		bool interact;
		bool oldInteract;
		
	protected:
		IInteraction* interaction;
		
	public:
		explicit Interactive_Simple(IInteraction* interaction);
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
	};
}
