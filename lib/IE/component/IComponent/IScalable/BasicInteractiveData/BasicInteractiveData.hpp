#pragma once

#include "../IScalable.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicInteractiveData {
	public:
		BasicInteractiveData(BoxPtr<typename IBasicInteraction<T>::Make>&& interaction, InitInfo init_info, T additional);
		
		BasicInteractiveData(BoxPtr<IBasicInteraction<T> >&& interaction, InitInfo init_info, T additional);
		
		explicit BasicInteractiveData(BoxPtr<IBasicInteraction<T> >&& interaction);
		
		void init(InitInfo init_info, T additional);
		
		void update();
		
		void update_interactions();
	
		InteractionStack* interaction_stack;
		InteractionManager* interaction_manager;
		BoxPtr<IBasicInteraction<T> > interaction;
	
	private:
		bool interact;
		bool old_interact;
	};
	
	using InteractiveData = BasicInteractiveData<>;
}

#include "BasicInteractiveData.inl"
