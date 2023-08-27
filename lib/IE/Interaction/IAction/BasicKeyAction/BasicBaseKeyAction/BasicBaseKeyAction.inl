namespace ie {
	template<typename T>
	BasicBaseKeyAction<T>::BasicBaseKeyAction() : mousePosition({0, 0}) {
	}
	
	template<typename T>
	void BasicBaseKeyAction<T>::setPressed(bool pressed) {
		if(this->pressed != pressed) {
			this->pressed = pressed;
			if(this->pressed) {
				startPressed();
			} else {
				stopPressed();
			}
		}
		BasicKeyAction<T>::setPressed(pressed);
	}
	
	template<typename T>
	void BasicBaseKeyAction<T>::update(sf::Vector2i mousePosition, bool press) {
		this->mousePosition = mousePosition;
		setPressed(press);
		if(this->pressed) {
			whilePressed();
		} else {
			whileNotPressed();
		}
	}
	
	template<typename T>
	void BasicBaseKeyAction<T>::init(BasicInteractionInitInfo<T>) {
	}
}
