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
		action(make.action->make(init_info)), key(make.key) {
	}
	
	template<typename T>
	BasicOneKeyInteraction<T>::BasicOneKeyInteraction(BoxPtr<BasicKeyAction<T> >&& action, Key key) :
		action(std::move(action)), key(key) {
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::init(BasicActionInitInfo<T> init_info) {
		action->init(init_info);
	}
	
	template<typename T>
	Key BasicOneKeyInteraction<T>::get_key() {
		return key;
	}
	
	template<typename T>
	BasicKeyAction<T>& BasicOneKeyInteraction<T>::get_action() {
		return *action;
	}
	
	template<typename T>
	const BasicKeyAction<T>& BasicOneKeyInteraction<T>::get_action() const {
		return *action;
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::set_action(BoxPtr<BasicKeyAction<T> >&& action) {
		this->action = std::move(action);
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::start(sf::Vector2i) {
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::update(sf::Vector2i mouse_position) {
		action->update(mouse_position, KeyHandler::is_key_pressed(key));
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::finish(sf::Vector2i) {
		action->set_pressed(false);
	}
	
	template<typename T>
	BasicOneKeyInteraction<T>* BasicOneKeyInteraction<T>::copy() {
		return new BasicOneKeyInteraction<T>{*this};
	}
	
	template<typename T>
	bool DecodePointer<BasicOneKeyInteraction<T> >::decode_pointer(const YAML::Node& node, BasicOneKeyInteraction<T>*& one_key_interaction) {
		one_key_interaction = new BasicOneKeyInteraction<T>{
			node["action"].as<BoxPtr<BasicKeyAction<T> > >(),
			conv_def(node["key"], Key::MouseLeft)
		};
		return true;
	}
}
