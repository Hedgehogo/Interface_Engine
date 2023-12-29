namespace ie {
	template<typename T>
	BasicInteractiveData<T>::BasicInteractiveData(BoxPtr<typename IBasicInteraction<T>::Make>&& interaction, InitInfo init_info, T additional) :
		interaction_stack(&init_info.interaction_stack),
		interaction_manager(&init_info.interaction_manager),
		interaction(interaction->make({init_info, additional})),
		interact_(false),
		old_interact_(false) {
	}
	
	template<typename T>
	BasicInteractiveData<T>::BasicInteractiveData(BoxPtr<IBasicInteraction<T> >&& interaction, InitInfo init_info, T additional) :
		interaction_stack(&init_info.interaction_stack),
		interaction_manager(&init_info.interaction_manager),
		interaction(std::move(interaction)),
		interact_(false),
		old_interact_(false) {
		this->interaction->init({init_info, additional});
	}
	
	template<typename T>
	BasicInteractiveData<T>::BasicInteractiveData(BoxPtr<IBasicInteraction<T> >&& interaction) :
		interaction_stack(nullptr), interaction_manager(nullptr), interaction(std::move(interaction)), interact_(false), old_interact_(false) {
	}
	
	template<typename T>
	void BasicInteractiveData<T>::init(InitInfo init_info, T additional) {
		this->interaction_stack = &init_info.interaction_stack;
		this->interaction_manager = &init_info.interaction_manager;
		interaction->init({init_info, additional});
	}
	
	template<typename T>
	void BasicInteractiveData<T>::update() {
		if(interact_ != old_interact_) {
			old_interact_ = interact_;
			if(interact_) {
				interaction_manager->add_interaction(*interaction);
			} else {
				interaction_manager->delete_interaction(*interaction);
			}
		}
		interact_ = false;
	}
	
	template<typename T>
	void BasicInteractiveData<T>::update_interactions() {
		interact_ = true;
	}
}
