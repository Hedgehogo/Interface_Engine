namespace ie {
	namespace make_system {
		template<typename T>
		BasicPressedInteraction<T>::BasicPressedInteraction(BoxPtr<BasicKeyAction<T> >&& action, Key key) :
			BasicOneKeyInteraction<T>(std::move(action), key) {
		}
		
		template<typename T>
		auto BasicPressedInteraction<T>::make(BasicActionInitInfo<T> init_info) -> ie::BasicPressedInteraction<T>* {
			return new ie::BasicPressedInteraction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicPressedInteraction<T>::BasicPressedInteraction(Make&& make, BasicActionInitInfo<T> init_info) :
		BasicOneKeyInteraction<T>({std::move(make.action), make.key}, init_info), interaction_manager_(&init_info.interaction_manager) {
	}
	
	template<typename T>
	auto BasicPressedInteraction<T>::update(sf::Vector2i mouse_position) -> void {
		if(key_handler_->get_key(this->key_)) {
			this->action_->update(mouse_position, true);
		} else {
			this->action_->update(mouse_position, false);
			interaction_manager_->delete_interaction(*this);
		}
	}
}
