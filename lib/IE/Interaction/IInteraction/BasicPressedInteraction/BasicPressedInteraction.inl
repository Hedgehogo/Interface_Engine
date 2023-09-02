namespace ie {
	template<typename T>
	BasicPressedInteraction<T>::Make::Make(BoxPtr<typename BasicKeyAction<T>::Make>&& action, Key key) :
		BasicOneKeyInteraction<T>::Make(std::move(action), key) {
	}
	
	template<typename T>
	BasicPressedInteraction<T>* BasicPressedInteraction<T>::Make::make(BasicActionInitInfo<T> initInfo) {
		return new BasicPressedInteraction<T>{std::move(*this), initInfo};
	}
	
	template<typename T>
	BasicPressedInteraction<T>::BasicPressedInteraction(Make&& make, BasicActionInitInfo<T> initInfo) :
		BasicOneKeyInteraction<T>({std::move(make.action), make.key}, initInfo), interactionManager(&initInfo.interactionManager) {
	}
	
	template<typename T>
	BasicPressedInteraction<T>::BasicPressedInteraction(BoxPtr<BasicKeyAction<T> >&& action, Key key) :
		BasicOneKeyInteraction<T>(std::move(action), key), interactionManager(nullptr) {
	}
	
	template<typename T>
	void BasicPressedInteraction<T>::init(BasicActionInitInfo<T> initInfo) {
		BasicOneKeyInteraction<T>::init(initInfo);
		this->interactionManager = &initInfo.interactionManager;
	}
	
	template<typename T>
	void BasicPressedInteraction<T>::update(sf::Vector2i mousePosition) {
		if(KeyHandler::isKeyPressed(this->key)) {
			this->action->update(mousePosition, true);
		} else {
			this->action->update(mousePosition, false);
			interactionManager->deleteInteraction(*this);
		}
	}
	
	template<typename T>
	BasicPressedInteraction<T>* BasicPressedInteraction<T>::copy() {
		return new BasicPressedInteraction<T>{*this};
	}
}
