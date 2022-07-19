#pragma once
#include "../../iInteractive/iInteractive.h"

namespace ui {
	class Interactive_Simple : public virtual IScalable, public IInteractive {
	private:
		bool interact;
		bool oldInteract;
		
	protected:
		IInteraction* interaction;
		
		void copy(Interactive_Simple* interactive_Simple);
		
	public:
		explicit Interactive_Simple(IInteraction* interaction);
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
	};
}
