namespace ie {
	template<typename T>
	BasicInteractiveData<T>::BasicInteractiveData(BoxPtr<typename IBasicInteraction<T>::Make>&& interaction, InitInfo init_info, T additional) :
		interaction(interaction->make({init_info, additional})) {
	}
	
	template<typename T>
	BasicInteractiveData<T>::BasicInteractiveData(BoxPtr<IBasicInteraction<T> >&& interaction, InitInfo init_info) :
		interaction(std::move(interaction)) {
	}
	
	template<typename T>
	auto BasicInteractiveData<T>::update() -> void {
		interaction->update();
	}
	
	template<typename T>
	auto BasicInteractiveData<T>::handle_event(Event event) -> bool {
		return interaction->handle_event(event);
	}
}
