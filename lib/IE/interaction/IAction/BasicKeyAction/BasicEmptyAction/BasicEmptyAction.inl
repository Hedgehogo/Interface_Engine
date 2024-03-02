namespace ie {
	namespace make_system {
		template<typename T>
		auto BasicEmptyAction<T>::make(BasicActionInitInfo<T> init_info) -> ie::BasicEmptyAction<T>* {
			return new ie::BasicEmptyAction<T>{std::move(*this), init_info};
		}
	}
	
	template<typename T>
	BasicEmptyAction<T>::BasicEmptyAction(Make&&, BasicActionInitInfo<T>) {
	}
	
	template<typename T>
	BasicEmptyAction<T>::BasicEmptyAction() {
	}
	
	template<typename T>
	auto BasicEmptyAction<T>::update(sf::Vector2i, bool) -> void {
	}
}
