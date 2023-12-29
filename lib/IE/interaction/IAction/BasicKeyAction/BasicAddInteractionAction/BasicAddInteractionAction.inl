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
		interaction_manager_(&init_info.interaction_manager), interaction_(make.interaction->make(init_info)) {
	}
	
	template<typename T>
	BasicAddInteractionAction<T>::BasicAddInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction) :
		interaction_manager_(nullptr), interaction_(std::move(interaction)) {
	}
	
	template<typename T>
	void BasicAddInteractionAction<T>::init(BasicActionInitInfo<T> init_info) {
		interaction_manager_ = &init_info.interaction_manager;
		interaction_->init(init_info);
	}
	
	template<typename T>
	IBasicInteraction<T>& BasicAddInteractionAction<T>::get_interaction() {
		return *interaction_;
	}
	
	template<typename T>
	BasicAddInteractionAction<T>* BasicAddInteractionAction<T>::copy() {
		return new BasicAddInteractionAction<T>{*this};
	}
	
	template<typename T>
	void BasicAddInteractionAction<T>::start_pressed() {
		interaction_manager_->add_interaction(*interaction_);
	}
	
	template<typename T>
	void BasicAddInteractionAction<T>::stop_pressed() {
		interaction_manager_->delete_interaction(*interaction_);
	}
	
	template<typename T>
	void BasicAddInteractionAction<T>::while_pressed() {
	}
	
	template<typename T>
	void BasicAddInteractionAction<T>::while_not_pressed() {
	}
}
