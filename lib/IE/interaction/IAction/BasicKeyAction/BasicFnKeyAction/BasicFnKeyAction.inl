namespace ie {
	namespace make_system {
		template<typename T>
		BasicFnKeyAction<T>::BasicFnKeyAction(FnType start_pressed_fn, FnType while_pressed_fn, FnType stop_pressed_fn, FnType while_not_pressed_fn) :
			start_pressed_fn(std::move(start_pressed_fn)),
			while_pressed_fn(std::move(while_pressed_fn)),
			stop_pressed_fn(std::move(stop_pressed_fn)),
			while_not_pressed_fn(std::move(while_not_pressed_fn)) {
		}
		
		template<typename T>
		ie::BasicFnKeyAction<T>* BasicFnKeyAction<T>::make(BasicActionInitInfo<T> init_info) {
			return new ie::BasicFnKeyAction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicFnKeyAction<T>::BasicFnKeyAction(Make&& make, BasicActionInitInfo<T>) :
		start_pressed_fn_(std::move(make.start_pressed_fn)),
		while_pressed_fn_(std::move(make.while_pressed_fn)),
		stop_pressed_fn_(std::move(make.stop_pressed_fn)),
		while_not_pressed_fn_(std::move(make.while_not_pressed_fn)) {
	}
	
	template<typename T>
	BasicFnKeyAction<T>::BasicFnKeyAction(FnType start_pressed_fn, FnType while_pressed_fn, FnType stop_pressed_fn, FnType while_not_pressed_fn) :
		start_pressed_fn_(std::move(start_pressed_fn)),
		while_pressed_fn_(std::move(while_pressed_fn)),
		stop_pressed_fn_(std::move(stop_pressed_fn)),
		while_not_pressed_fn_(std::move(while_not_pressed_fn)) {
	}
	
	template<typename T>
	void BasicFnKeyAction<T>::start_pressed() {
		start_pressed_fn_(this->point_position_);
	}
	
	template<typename T>
	void BasicFnKeyAction<T>::stop_pressed() {
		stop_pressed_fn_(this->point_position_);
	}
	
	template<typename T>
	void BasicFnKeyAction<T>::while_pressed() {
		while_pressed_fn_(this->point_position_);
	}
	
	template<typename T>
	void BasicFnKeyAction<T>::while_not_pressed() {
		while_not_pressed_fn_(this->point_position_);
	}
}

