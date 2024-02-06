namespace ie {
	namespace make_system {
		template<typename T>
		BasicOneKeyInteraction<T>::BasicOneKeyInteraction(BoxPtr<BasicKeyAction<T> >&& action, Key key) :
			action(std::move(action)), key(key) {
		}
		
		template<typename T>
		ie::BasicOneKeyInteraction<T>* BasicOneKeyInteraction<T>::make(BasicActionInitInfo<T> init_info) {
			return new ie::BasicOneKeyInteraction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicOneKeyInteraction<T>::BasicOneKeyInteraction(Make&& make, BasicActionInitInfo<T> init_info) :
		action_(make.action->make(init_info)), key_(make.key) {
	}
	
	template<typename T>
	Key BasicOneKeyInteraction<T>::get_key() {
		return key_;
	}
	
	template<typename T>
	BasicKeyAction<T>& BasicOneKeyInteraction<T>::get_action() {
		return *action_;
	}
	
	template<typename T>
	const BasicKeyAction<T>& BasicOneKeyInteraction<T>::get_action() const {
		return *action_;
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::set_action(BoxPtr<BasicKeyAction<T> >&& action) {
		this->action_ = std::move(action);
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::start(sf::Vector2i) {
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::update(sf::Vector2i mouse_position) {
		action_->update(mouse_position, KeyHandler::is_key_pressed(key_));
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::finish(sf::Vector2i) {
		action_->set_pressed(false);
	}
}

template<typename T>
orl::Option<ie::make_system::BasicOneKeyInteraction<T> >
ieml::Decode<char, ie::make_system::BasicOneKeyInteraction<T> >::decode(ieml::Node const& node) {
	auto& clear_node{node.get_clear()};
	return ie::make_system::BasicOneKeyInteraction<T>{
		clear_node.at("action").except().template as<bp::BoxPtr<ie::make_system::BasicKeyAction<T> > > ().move_except(),
		clear_node.get_as<ie::Key>().ok_or(ie::Key::MouseLeft),
	};
}
