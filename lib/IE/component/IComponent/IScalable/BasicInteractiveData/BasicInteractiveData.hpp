#pragma once

#include "../IScalable.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicInteractiveData {
	public:
		BasicInteractiveData(BoxPtr<typename IBasicInteraction<T>::Make>&& interaction, InitInfo initInfo, T additional);
		
		BasicInteractiveData(BoxPtr<IBasicInteraction<T> >&& interaction, InitInfo initInfo, T additional);
		
		explicit BasicInteractiveData(BoxPtr<IBasicInteraction<T> >&& interaction);
		
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
	
	using InteractiveData = BasicInteractiveData<>;
}

#include "BasicInteractiveData.inl"
