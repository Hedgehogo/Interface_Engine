namespace ie {
	namespace make_system {
		template<typename T>
		BasicOneKeyInteraction<T>::BasicOneKeyInteraction(BoxPtr<BasicKeyAction<T> >&& action, Key key) :
			action(std::move(action)), key(key) {
		}
		
		template<typename T>
		auto BasicOneKeyInteraction<T>::make(BasicActionInitInfo<T> init_info) -> ie::BasicOneKeyInteraction<T>* {
			return new ie::BasicOneKeyInteraction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicOneKeyInteraction<T>::BasicOneKeyInteraction(Make&& make, BasicActionInitInfo<T> init_info) :
		key_handler_(&init_info.key_handler), action_(make.action->make(init_info)), key_(make.key) {
	}
	
	template<typename T>
	auto BasicOneKeyInteraction<T>::get_key() -> Key {
		return key_;
	}
	
	template<typename T>
	auto BasicOneKeyInteraction<T>::get_action() -> BasicKeyAction<T>& {
		return *action_;
	}
	
	template<typename T>
	auto BasicOneKeyInteraction<T>::get_action() const -> BasicKeyAction<T> const& {
		return *action_;
	}
	
	template<typename T>
	auto BasicOneKeyInteraction<T>::set_action(BoxPtr<BasicKeyAction<T> >&& action) -> void {
		this->action_ = std::move(action);
	}
	
	template<typename T>
	auto BasicOneKeyInteraction<T>::start(sf::Vector2i) -> void {
	}
	
	template<typename T>
	auto BasicOneKeyInteraction<T>::update(sf::Vector2i mouse_position) -> void {
		action_->update(mouse_position, key_handler_->is_key_pressed(key_));
	}
	
	template<typename T>
	auto BasicOneKeyInteraction<T>::finish(sf::Vector2i) -> void {
		action_->finish();
	}
}

template<typename T>
auto ieml::Decode<char, ie::make_system::BasicOneKeyInteraction<T> >::decode(
	ieml::Node const& node
) -> orl::Option<ie::make_system::BasicOneKeyInteraction<T> > {
	auto& clear_node{node.get_clear()};
	return ie::make_system::BasicOneKeyInteraction<T>{
		clear_node.at("action").except().template as<bp::BoxPtr<ie::make_system::BasicKeyAction<T> > >().except(),
		clear_node.get_as<ie::Key>("key").except().ok_or(ie::Key::MouseLeft),
	};
}
