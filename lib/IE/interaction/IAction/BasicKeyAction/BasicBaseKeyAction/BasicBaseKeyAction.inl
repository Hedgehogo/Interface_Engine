namespace ie {
	template<typename T>
	void BasicBaseKeyAction<T>::set_pressed(bool pressed) {
		if(this->pressed != pressed) {
			this->pressed = pressed;
			if(this->pressed) {
				start_pressed();
			} else {
				stop_pressed();
			}
		}
		BasicKeyAction<T>::set_pressed(pressed);
	}
	
	template<typename T>
	void BasicBaseKeyAction<T>::update(sf::Vector2i mouse_position, bool press) {
		this->mouse_position = mouse_position;
		set_pressed(press);
		if(this->pressed) {
			while_pressed();
		} else {
			while_not_pressed();
		}
	}
	
	template<typename T>
	void BasicBaseKeyAction<T>::init(BasicActionInitInfo<T>) {
	}
}
