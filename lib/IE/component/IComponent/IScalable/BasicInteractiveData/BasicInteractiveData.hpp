#pragma once

#include "../IScalable.hpp"

namespace ie {
	template<typename T = std::monostate>
	class BasicInteractiveData {
	public:
		BasicInteractiveData(BoxPtr<typename IBasicInteraction<T>::Make>&& interaction, InitInfo init_info, T additional);
		
		BasicInteractiveData(BoxPtr<IBasicInteraction<T> >&& interaction, InitInfo init_info);
		
		auto update() -> void;
		
		auto handle_event(Event event) -> bool;
	
		BoxPtr<IBasicInteraction<T> > interaction;
	};
	
	using InteractiveData = BasicInteractiveData<>;
}

#include "BasicInteractiveData.inl"
