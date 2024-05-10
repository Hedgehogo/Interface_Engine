namespace ie {
	namespace make_system {
		template<typename T>
		BasicAddBlockInteractionAction<T>::BasicAddBlockInteractionAction(BoxPtr<IBasicInteraction<T> >&& interaction) :
			BasicAddInteractionAction<T>(std::move(interaction)) {
		}
		
		template<typename T>
		auto BasicAddBlockInteractionAction<T>::make(BasicActionInitInfo<T> init_info) -> ie::BasicAddBlockInteractionAction<T>* {
			return new ie::BasicAddBlockInteractionAction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicAddBlockInteractionAction<T>::BasicAddBlockInteractionAction(Make&& make, BasicActionInitInfo<T> init_info) :
		BasicAddInteractionAction<T>(std::move(make), init_info) {
	}
	
	template<typename T>
	auto BasicAddBlockInteractionAction<T>::update(orl::Option<Touch> touch) -> void {
		if(this->tracker_.update(Touch::pressing(touch).is_some()).started()) {
			this->interaction_manager_->add_interaction(*this->interaction_);
		}
	}
	
	template<typename T>
	auto BasicAddBlockInteractionAction<T>::finish() -> void {
	}
}
