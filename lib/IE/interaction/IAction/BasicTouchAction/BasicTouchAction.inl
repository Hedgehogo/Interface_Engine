namespace ie {
	template<typename T>
	BasicTouchAction<T>::BasicTouchAction() : pressed_(false) {
	}
	
	template<typename T>
	auto BasicTouchAction<T>::set_pressed(bool pressed) -> void {
		this->pressed_ = pressed;
	}
}
