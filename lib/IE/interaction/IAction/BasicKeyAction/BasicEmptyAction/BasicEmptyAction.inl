namespace ie {
	namespace make_system {
		template<typename T>
		ie::BasicEmptyAction<T>* BasicEmptyAction<T>::make(BasicActionInitInfo<T> init_info) {
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
	void BasicEmptyAction<T>::update(sf::Vector2i, bool) {
	}
	
	template<typename T>
	BasicEmptyAction<T>* BasicEmptyAction<T>::copy() {
		return new BasicEmptyAction<T>{*this};
	}
}
