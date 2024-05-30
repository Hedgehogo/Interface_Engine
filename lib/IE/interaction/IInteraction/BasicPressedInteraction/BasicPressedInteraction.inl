namespace ie {
	namespace make_system {
		template<typename T>
		BasicPressedInteraction<T>::BasicPressedInteraction(BoxPtr<IBasicTouchAction<T> >&& action, Key key) :
			BasicTouchInteraction<T>(std::move(action), key) {
		}
		
		template<typename T>
		auto BasicPressedInteraction<T>::make(BasicActionInitInfo<T> init_info) -> ie::BasicPressedInteraction<T>* {
			return new ie::BasicPressedInteraction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicPressedInteraction<T>::BasicPressedInteraction(Make&& make, BasicActionInitInfo<T> init_info) :
		BasicTouchInteraction<T>({std::move(make.action), make.key}, init_info), interaction_manager_(&init_info.interaction_manager) {
	}
	
	template<typename T>
	auto BasicPressedInteraction<T>::update(sf::Vector2i) -> void {
		auto touch{this->tracker_.reset().map(Touch::from(this->event_handler_->get_key(this->key_)))};
		if(Touch::pressing(touch).is_some()) {
			this->action_->update(touch);
		} else {
			this->action_->update(touch);
			interaction_manager_->delete_interaction(*this);
		}
	}
}
