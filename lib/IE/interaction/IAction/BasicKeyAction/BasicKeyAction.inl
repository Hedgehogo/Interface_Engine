namespace ie {
	template<typename T>
	BasicKeyAction<T>::BasicKeyAction() : pressed_(false) {
	}
	
	template<typename T>
	auto BasicKeyAction<T>::set_pressed(bool pressed) -> void {
		this->pressed_ = pressed;
	}
}
