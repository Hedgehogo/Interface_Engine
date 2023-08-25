namespace ui {
	template<typename T>
	BasicOneKeyInteraction<T>::BasicOneKeyInteraction(BoxPtr<BasicKeyEvent<T> >&& event, Key key) :
		event(std::move(event)), key(key) {
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::init(BasicInteractionInitInfo<T> initInfo) {
		event->init(initInfo);
	}
	
	template<typename T>
	Key BasicOneKeyInteraction<T>::getKey() {
		return key;
	}
	
	template<typename T>
	BasicKeyEvent<T>& BasicOneKeyInteraction<T>::getEvent() {
		return *event;
	}
	
	template<typename T>
	const BasicKeyEvent<T>& BasicOneKeyInteraction<T>::getEvent() const {
		return *event;
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::setEvent(BoxPtr<BasicKeyEvent<T> >&& event) {
		this->event = std::move(event);
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::start(sf::Vector2i) {
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::update(sf::Vector2i mousePosition) {
		event->update(mousePosition, KeyHandler::isKeyPressed(key));
	}
	
	template<typename T>
	void BasicOneKeyInteraction<T>::finish(sf::Vector2i) {
		event->setPressed(false);
	}
	
	template<typename T>
	BasicOneKeyInteraction<T>* BasicOneKeyInteraction<T>::copy() {
		return new BasicOneKeyInteraction<T>{*this};
	}
	
	template<typename T>
	bool DecodePointer<BasicOneKeyInteraction<T> >::decodePointer(const YAML::Node& node, BasicOneKeyInteraction<T>*& oneKeyInteraction) {
		oneKeyInteraction = new BasicOneKeyInteraction<T>{
			node["event"].as<BoxPtr<BasicKeyEvent<T> > >(),
			convDef(node["key"], Key::mouseLeft)
		};
		return true;
	}
}
