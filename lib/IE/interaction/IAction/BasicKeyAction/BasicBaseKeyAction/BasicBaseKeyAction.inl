namespace ie {
	template<typename T>
	auto BasicBaseKeyAction<T>::set_pressed(bool pressed) -> void {
		if(this->pressed_ != pressed) {
			this->pressed_ = pressed;
			if(this->pressed_) {
				start_pressed();
			} else {
				stop_pressed();
			}
		}
		BasicKeyAction<T>::set_pressed(pressed);
	}
	
	template<typename T>
	auto BasicBaseKeyAction<T>::update(sf::Vector2i mouse_position, bool press) -> void {
		this->mouse_position_ = mouse_position;
		set_pressed(press);
		if(this->pressed_) {
			while_pressed();
		} else {
			while_not_pressed();
		}
	}
}
