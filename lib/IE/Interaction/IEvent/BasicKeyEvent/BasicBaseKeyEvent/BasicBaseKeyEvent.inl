namespace ui {
	template<typename T>
	BasicBaseKeyEvent<T>::BasicBaseKeyEvent() : mousePosition({0, 0}) {
	}
	
	template<typename T>
	void BasicBaseKeyEvent<T>::setPressed(bool pressed) {
		if(this->pressed != pressed) {
			this->pressed = pressed;
			if(this->pressed) {
				startPressed();
			} else {
				stopPressed();
			}
		}
		BasicKeyEvent<T>::setPressed(pressed);
	}
	
	template<typename T>
	void BasicBaseKeyEvent<T>::update(sf::Vector2i mousePosition, bool press) {
		this->mousePosition = mousePosition;
		setPressed(press);
		if(this->pressed) {
			whilePressed();
		} else {
			whileNotPressed();
		}
	}
	
	template<typename T>
	void BasicBaseKeyEvent<T>::init(BasicInteractionInitInfo<T>) {
	}
}
