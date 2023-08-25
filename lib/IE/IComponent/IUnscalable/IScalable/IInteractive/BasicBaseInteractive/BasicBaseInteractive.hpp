#pragma once

#include "IE/IComponent/IUnscalable/IInteractive/IInteractive.hpp"

namespace ui {
	template<typename T = std::monostate>
	class BasicBaseInteractiveData {
	public:
		BasicBaseInteractiveData(BoxPtr<IBasicInteraction<T> >&& interaction, InitInfo initInfo, T additional);
		
		explicit BasicBaseInteractiveData(BoxPtr<IBasicInteraction<T> >&& interaction);
		
		void init(InitInfo initInfo, T additional);
		
		void update();
		
		void updateInteractions();
	
		InteractionStack* interactionStack;
		InteractionManager* interactionManager;
		BoxPtr<IBasicInteraction<T> > interaction;
	
	private:
		bool interact;
		bool oldInteract;
	};
	
	using BaseInteractiveData = BasicBaseInteractiveData<>;
	
	template<typename T = std::monostate>
	class BasicBaseInteractive : public virtual IScalable, public IInteractive, public IUpdatable {
	public:
		BasicBaseInteractive(BoxPtr<IBasicInteraction<T> >&& interaction, InitInfo initInfo, T additional);
		
		explicit BasicBaseInteractive(BoxPtr<IBasicInteraction<T> >&& interaction);
		
		virtual void init(InitInfo initInfo, T additional);
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
	
	protected:
		BasicBaseInteractiveData<T> interactive;
	};
	
	using BaseInteractive = BasicBaseInteractive<>;
}

#include "BasicBaseInteractive.inl"
