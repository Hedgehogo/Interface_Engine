namespace ie {
	namespace make_system {
		template<typename T>
		BasicFnInteraction<T>::BasicFnInteraction(FnType start_fn, FnType finish_fn) :
			start_fn(std::move(start_fn)), finish_fn(std::move(finish_fn)) {
		}
		
		template<typename T>
		ie::BasicFnInteraction<T>* BasicFnInteraction<T>::make(BasicActionInitInfo<T> init_info) {
			return new ie::BasicFnInteraction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicFnInteraction<T>::BasicFnInteraction(Make&& make, BasicActionInitInfo<T>) :
		start_fn(std::move(make.start_pointing)), finish_fn(std::move(make.finish_pointing)) {
	}
	
	template<typename T>
	BasicFnInteraction<T>::BasicFnInteraction(FnType start_fn, FnType finish_fn) :
		start_fn(std::move(start_fn)), finish_fn(std::move(finish_fn)) {
	}
	
	template<typename T>
	void BasicFnInteraction<T>::start(sf::Vector2i mouse_position) {
		start_fn(mouse_position);
	}
	
	template<typename T>
	void BasicFnInteraction<T>::finish(sf::Vector2i mouse_position) {
		finish_fn(mouse_position);
	}
}
