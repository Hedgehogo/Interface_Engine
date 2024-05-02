namespace ie {
	namespace make_system {
		template<typename T>
		BasicFnInteraction<T>::BasicFnInteraction(FnType start_fn, FnType finish_fn) :
			start_fn(std::move(start_fn)), finish_fn(std::move(finish_fn)) {
		}
		
		template<typename T>
		auto BasicFnInteraction<T>::make(BasicActionInitInfo<T> init_info) -> ie::BasicFnInteraction<T>* {
			return new ie::BasicFnInteraction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicFnInteraction<T>::BasicFnInteraction(Make&& make, BasicActionInitInfo<T>) :
		start_fn_(std::move(make.start_pointing)), finish_fn_(std::move(make.finish_pointing)) {
	}
	
	template<typename T>
	BasicFnInteraction<T>::BasicFnInteraction(FnType start_fn, FnType finish_fn) :
		start_fn_(std::move(start_fn)), finish_fn_(std::move(finish_fn)) {
	}
	
	template<typename T>
	auto BasicFnInteraction<T>::start(sf::Vector2i point_position) -> void {
		start_fn_(point_position);
	}
	
	template<typename T>
	auto BasicFnInteraction<T>::finish(sf::Vector2i point_position) -> void {
		finish_fn_(point_position);
	}
}
