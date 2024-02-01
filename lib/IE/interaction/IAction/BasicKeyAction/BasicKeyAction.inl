namespace ie {
	template<typename T>
	BasicKeyAction<T>::BasicKeyAction() : pressed_(false) {
	}
	
	template<typename T>
	void BasicKeyAction<T>::set_pressed(bool pressed) {
		this->pressed_ = pressed;
	}
}
