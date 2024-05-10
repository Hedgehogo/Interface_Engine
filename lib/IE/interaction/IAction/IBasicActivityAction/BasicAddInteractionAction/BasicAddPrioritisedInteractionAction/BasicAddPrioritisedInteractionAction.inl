namespace ie {
	namespace make_system {
		template<typename T>
		BasicAddPrioritisedInteractionAction<T>::BasicAddPrioritisedInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction) :
			BasicAddInteractionAction<T>(std::move(interaction)) {
		}
		
		template<typename T>
		auto BasicAddPrioritisedInteractionAction<T>::make(BasicActionInitInfo<T> init_info) -> ie::BasicAddPrioritisedInteractionAction<T>* {
			return new ie::BasicAddPrioritisedInteractionAction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicAddPrioritisedInteractionAction<T>::BasicAddPrioritisedInteractionAction(Make&& make, BasicActionInitInfo<T> init_info) :
		BasicAddInteractionAction<T>(std::move(make), init_info) {
	}
	
	template<typename T>
	auto BasicAddPrioritisedInteractionAction<T>::update(bool active) -> void {
		if(this->tracker_.update(active).started()) {
			this->interaction_manager_->add_interaction(*this->interaction_);
		}
	}
	
	template<typename T>
	auto BasicAddPrioritisedInteractionAction<T>::finish() -> void {
	}
}
