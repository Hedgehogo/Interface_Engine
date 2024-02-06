#pragma once

#include "../IScalable.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicInteractiveData {
	public:
		BasicInteractiveData(BoxPtr<typename IBasicInteraction<T>::Make>&& interaction, InitInfo init_info, T additional);
		
		BasicInteractiveData(BoxPtr<IBasicInteraction<T> >&& interaction, InitInfo init_info);
		
		void update();
		
		void update_interactions();
	
		InteractionManager* interaction_manager;
		BoxPtr<IBasicInteraction<T> > interaction;
	
	private:
		bool interact_;
		bool old_interact_;
	};
	
	using InteractiveData = BasicInteractiveData<>;
}

#include "BasicInteractiveData.inl"
