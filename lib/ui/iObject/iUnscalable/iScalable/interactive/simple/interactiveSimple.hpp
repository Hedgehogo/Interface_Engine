#pragma once

#include "ui/iObject/iUnscalable/interactive/iInteractive.hpp"

namespace ui {
	class Interactive_Simple : public virtual IScalable, public IInteractive, public IUpdatable {
	public:
		explicit Interactive_Simple(BoxPtr<IInteraction>&& interaction);
		
		void init(InitInfo initInfo) override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
	
	protected:
		InteractionStack* interactionStack;
		InteractionManager* interactionManager;
		BoxPtr<IInteraction> interaction;
	
	private:
		bool interact;
		bool oldInteract;
	};
}
