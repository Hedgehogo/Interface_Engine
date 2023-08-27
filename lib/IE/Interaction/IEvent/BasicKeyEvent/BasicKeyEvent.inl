namespace ie {
	template<typename T>
	BasicKeyEvent<T>::BasicKeyEvent() : pressed(false) {
	}
	
	template<typename T>
	void BasicKeyEvent<T>::init(BasicInteractionInitInfo<T>) {
	}
	
	template<typename T>
	void BasicKeyEvent<T>::setPressed(bool pressed) {
		this->pressed = pressed;
	}
}
