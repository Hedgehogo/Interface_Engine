#pragma once

#include "IE/IComponent/IUnscalable/IInteractive/IInteractive.hpp"

namespace ui {
	class BaseInteractiveData {
	public:
		BaseInteractiveData(BoxPtr<IInteraction>&& interaction, InitInfo initInfo);
		
		explicit BaseInteractiveData(BoxPtr<IInteraction>&& interaction);
		
		void init(InitInfo initInfo);
		
		void update();
		
		void updateInteractions();
	
		InteractionStack* interactionStack;
		InteractionManager* interactionManager;
		BoxPtr<IInteraction> interaction;
	
	private:
		bool interact;
		bool oldInteract;
	};
	
	class BaseInteractive : public virtual IScalable, public IInteractive, public IUpdatable {
	public:
		BaseInteractive(BoxPtr<IInteraction>&& interaction, InitInfo initInfo);
		
		explicit BaseInteractive(BoxPtr<IInteraction>&& interaction);
		
		void init(InitInfo initInfo) override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
	
	protected:
		BaseInteractiveData interactive;
	};
}
