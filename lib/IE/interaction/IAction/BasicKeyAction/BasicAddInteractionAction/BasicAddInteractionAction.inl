namespace ie {
	namespace make_system {
		template<typename T>
		BasicAddInteractionAction<T>::BasicAddInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction) :
			interaction(std::move(interaction)) {
		}
		
		template<typename T>
		ie::BasicAddInteractionAction<T>* BasicAddInteractionAction<T>::make(BasicActionInitInfo<T> init_info) {
			return new ie::BasicAddInteractionAction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicAddInteractionAction<T>::BasicAddInteractionAction(Make&& make, BasicActionInitInfo<T> init_info) :
		interaction_manager(&init_info.interaction_manager), interaction(make.interaction->make(init_info)) {
	}
	
	template<typename T>
	BasicAddInteractionAction<T>::BasicAddInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction) :
		interaction_manager(nullptr), interaction(std::move(interaction)) {
	}
	
	template<typename T>
	void BasicAddInteractionAction<T>::init(BasicActionInitInfo<T> init_info) {
		interaction_manager = &init_info.interaction_manager;
		interaction->init(init_info);
	}
	
	template<typename T>
	IBasicInteraction<T>& BasicAddInteractionAction<T>::get_interaction() {
		return *interaction;
	}
	
	template<typename T>
	BasicAddInteractionAction<T>* BasicAddInteractionAction<T>::copy() {
		return new BasicAddInteractionAction<T>{*this};
	}
	
	template<typename T>
	void BasicAddInteractionAction<T>::start_pressed() {
		interaction_manager->add_interaction(*interaction);
	}
	
	template<typename T>
	void BasicAddInteractionAction<T>::stop_pressed() {
		interaction_manager->delete_interaction(*interaction);
	}
	
	template<typename T>
	void BasicAddInteractionAction<T>::while_pressed() {
	}
	
	template<typename T>
	void BasicAddInteractionAction<T>::while_not_pressed() {
	}
}
