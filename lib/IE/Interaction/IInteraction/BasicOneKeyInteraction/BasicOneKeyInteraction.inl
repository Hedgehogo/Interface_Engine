namespace ie {
	template<typename T>
	BasicOneKeyInteraction<T>::BasicOneKeyInteraction(BoxPtr<BasicKeyAction<T> >&& action, Key key) :
		action(std::move(action)), key(key) {
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::init(BasicInteractionInitInfo<T> initInfo) {
		action->init(initInfo);
	}
	
	template<typename T>
	Key BasicOneKeyInteraction<T>::getKey() {
		return key;
	}
	
	template<typename T>
	BasicKeyAction<T>& BasicOneKeyInteraction<T>::getAction() {
		return *action;
	}
	
	template<typename T>
	const BasicKeyAction<T>& BasicOneKeyInteraction<T>::getAction() const {
		return *action;
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::setAction(BoxPtr<BasicKeyAction<T> >&& action) {
		this->action = std::move(action);
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::start(sf::Vector2i) {
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::update(sf::Vector2i mousePosition) {
		action->update(mousePosition, KeyHandler::isKeyPressed(key));
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::finish(sf::Vector2i) {
		action->setPressed(false);
	}
	
	template<typename T>
	BasicOneKeyInteraction<T>* BasicOneKeyInteraction<T>::copy() {
		return new BasicOneKeyInteraction<T>{*this};
	}
	
	template<typename T>
	bool DecodePointer<BasicOneKeyInteraction<T> >::decodePointer(const YAML::Node& node, BasicOneKeyInteraction<T>*& oneKeyInteraction) {
		oneKeyInteraction = new BasicOneKeyInteraction<T>{
			node["action"].as<BoxPtr<BasicKeyAction<T> > >(),
			convDef(node["key"], Key::mouseLeft)
		};
		return true;
	}
}
