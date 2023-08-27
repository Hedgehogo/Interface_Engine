namespace ie {
	template<typename T>
	BasicPressedInteraction<T>::BasicPressedInteraction(BoxPtr<BasicKeyEvent<T> >&& event, Key key) :
		BasicOneKeyInteraction<T>(std::move(event), key), interactionManager(nullptr) {
	}
	
	template<typename T>
	void BasicPressedInteraction<T>::init(BasicInteractionInitInfo<T> initInfo) {
		this->interactionManager = &initInfo.interactionManager;
	}
	
	template<typename T>
	void BasicPressedInteraction<T>::update(sf::Vector2i mousePosition) {
		if(KeyHandler::isKeyPressed(this->key)) {
			this->event->update(mousePosition, true);
		} else {
			this->event->update(mousePosition, false);
			interactionManager->deleteInteraction(*this);
		}
	}
	
	template<typename T>
	BasicPressedInteraction<T>* BasicPressedInteraction<T>::copy() {
		return new BasicPressedInteraction<T>{*this};
	}
}
