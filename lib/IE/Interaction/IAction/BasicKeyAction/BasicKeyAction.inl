namespace ie {
	template<typename T>
	BasicKeyAction<T>::BasicKeyAction() : pressed(false) {
	}
	
	template<typename T>
	void BasicKeyAction<T>::init(BasicInteractionInitInfo<T>) {
	}
	
	template<typename T>
	void BasicKeyAction<T>::setPressed(bool pressed) {
		this->pressed = pressed;
	}
}
